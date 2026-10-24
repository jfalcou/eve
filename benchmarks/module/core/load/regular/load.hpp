//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <algorithm>
#include <cstdint>
#include <random>
#include <string>
#include <vector>

// One number per register size (16, 32 and 64 bytes, as supported): the cost of a partial load.
// Each iteration does one ignore_first, one ignore_last and one ignore_extrema load, each taken
// from a shuffled, pre-computed list of {ptr, ignore} cases.
// Pointers land at the beginning and the end of a 4kb page aligned buffer, or straddle it with the
// out-of-page lanes ignored.

using T = EVE_VALUE;

template<typename C> struct load_case
{
  T const*  ptr;
  C         ignore;
};

// Pointers outside of the page are never dereferenced for their ignored lanes, compute them as
// integers to not form out of bounds pointers.
T const* at(T const* p, std::ptrdiff_t n)
{
  return reinterpret_cast<T const*>(reinterpret_cast<std::intptr_t>(p) + n * std::ptrdiff_t(sizeof(T)));
}

template<typename C> auto sample(std::vector<load_case<C>> all, std::size_t n, std::mt19937& g)
{
  std::vector<load_case<C>> res;
  res.reserve(n);
  while( res.size() < n )
  {
    std::shuffle(all.begin(), all.end(), g);
    res.insert(res.end(), all.begin(), all.begin() + std::min(all.size(), n - res.size()));
  }
  return res;
}

template<std::ptrdiff_t Bytes> void run(ankerl::nanobench::Bench& b, T const* begin, T const* end)
{
  using w_t = eve::wide<T, Bytes / sizeof(T)>;
  constexpr std::ptrdiff_t N = w_t::size();

  // In page addresses: the first and the last N loadable positions.
  std::vector<T const*> in_page;
  for( std::ptrdiff_t i = 0; i < N; ++i )
  {
    in_page.push_back(begin + i);
    in_page.push_back(end - N - i);
  }

  std::vector<load_case<eve::ignore_first>>   firsts;
  std::vector<load_case<eve::ignore_last>>    lasts;
  std::vector<load_case<eve::ignore_extrema>> extremas;

  for( std::ptrdiff_t k = 0; k < N; ++k )
  {
    for( auto p : in_page )
    {
      firsts.push_back({p, eve::ignore_first(k)});
      lasts.push_back({p, eve::ignore_last(k)});
    }

    // Before the page / after the page, out of page lanes are ignored.
    for( std::ptrdiff_t j = 1; j <= k; ++j )
    {
      firsts.push_back({at(begin, -j), eve::ignore_first(k)});
      lasts.push_back({at(end, j - N), eve::ignore_last(k)});
    }
  }

  for( std::ptrdiff_t f = 0; f < N; ++f )
  {
    for( std::ptrdiff_t l = 0; f + l < N; ++l )
    {
      for( auto p : in_page ) extremas.push_back({p, eve::ignore_extrema(f, l)});
      for( std::ptrdiff_t j = 1; j <= f; ++j ) extremas.push_back({at(begin, -j), eve::ignore_extrema(f, l)});
      for( std::ptrdiff_t j = 1; j <= l; ++j ) extremas.push_back({at(end, j - N), eve::ignore_extrema(f, l)});
    }
  }

  constexpr std::size_t cases = 4096;
  std::mt19937 g{42};
  auto first_cases   = sample(firsts, cases, g);
  auto last_cases    = sample(lasts, cases, g);
  auto extrema_cases = sample(extremas, cases, g);

  b.batch(3 * cases);
  b.run ( "load[ignore] - " + std::to_string(Bytes) + " bytes"
        , [&]
          {
            for( std::size_t i = 0; i < cases; ++i )
            {
              auto f = eve::load[first_cases[i].ignore](first_cases[i].ptr, eve::as<w_t>{});
              auto l = eve::load[last_cases[i].ignore](last_cases[i].ptr, eve::as<w_t>{});
              auto e = eve::load[extrema_cases[i].ignore](extrema_cases[i].ptr, eve::as<w_t>{});
              ankerl::nanobench::doNotOptimizeAway(f);
              ankerl::nanobench::doNotOptimizeAway(l);
              ankerl::nanobench::doNotOptimizeAway(e);
            }
          }
        );
}

int main()
{
  constexpr std::ptrdiff_t page_n = 4096 / sizeof(T);
  std::vector<T, eve::aligned_allocator<T, page_n>> page(page_n, T{1});

  T const* begin = page.data();
  T const* end   = page.data() + page_n;

  ankerl::nanobench::Bench b;
  b.unit("load").minEpochIterations(1000).performanceCounters(true);

  run<16>(b, begin, end);
  if constexpr( eve::current_api >= eve::avx    ) run<32>(b, begin, end);
  if constexpr( eve::current_api >= eve::avx512 ) run<64>(b, begin, end);
}
