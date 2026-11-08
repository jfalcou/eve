//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <random>
#include <vector>

// The cost of a partial load of a native register.
// Loads come from pre-computed lists of {ptr, ignore} cases, one per kind of ignore. Every case is
// drawn independently: first the ignore (uniformly), then a pointer valid for it (uniformly).
// Pointers land at the beginning and the end of a 4kb page aligned buffer, or straddle it with the
// out-of-page lanes ignored.
// The lists are long enough for the branch predictor not to learn them.
//
// load[ignore]         : the overall number, one load of each kind per step
// load[ignore_first]...: each kind on its own

using T   = EVE_VALUE;
using w_t = eve::wide<T>;

template<typename C> struct load_case
{
  T const*  ptr;
  C         ignore;
};

// This is not std::sample, because we want to select more elements out than there were on the input.
// And repeating elements are fine.
template<typename C>
auto sample(std::vector<std::vector<load_case<C>>> const& groups, std::size_t n, std::mt19937& g)
{
  std::uniform_int_distribution<std::size_t> pick_group(0, groups.size() - 1);

  std::vector<load_case<C>> res;
  res.reserve(n);
  while( res.size() < n )
  {
    auto const& group = groups[pick_group(g)];
    res.push_back(group[std::uniform_int_distribution<std::size_t>(0, group.size() - 1)(g)]);
  }
  return res;
}

void run(ankerl::nanobench::Bench& b, T const* begin, T const* end, std::size_t cases)
{
  constexpr std::ptrdiff_t N = w_t::size();

  // In page addresses: the first and the last N loadable positions.
  std::vector<T const*> in_page;
  for( std::ptrdiff_t i = 0; i < N; ++i )
  {
    in_page.push_back(begin + i);
    in_page.push_back(end - N - i);
  }

  std::vector<std::vector<load_case<eve::ignore_first>>>   firsts;
  std::vector<std::vector<load_case<eve::ignore_last>>>    lasts;
  std::vector<std::vector<load_case<eve::ignore_extrema>>> extremas;

  for( std::ptrdiff_t k = 0; k < N; ++k )
  {
    auto& f = firsts.emplace_back();
    auto& l = lasts.emplace_back();

    for( auto p : in_page )
    {
      f.push_back({p, eve::ignore_first(k)});
      l.push_back({p, eve::ignore_last(k)});
    }

    // Before the page / after the page, out of page lanes are ignored.
    for( std::ptrdiff_t j = 1; j <= k; ++j )
    {
      f.push_back({begin - j, eve::ignore_first(k)});
      l.push_back({end - N + j, eve::ignore_last(k)});
    }
  }

  for( std::ptrdiff_t f = 0; f < N; ++f )
  {
    for( std::ptrdiff_t l = 0; f + l < N; ++l )
    {
      auto& e = extremas.emplace_back();
      for( auto p : in_page ) e.push_back({p, eve::ignore_extrema(f, l)});
      for( std::ptrdiff_t j = 1; j <= f; ++j ) e.push_back({begin - j, eve::ignore_extrema(f, l)});
      for( std::ptrdiff_t j = 1; j <= l; ++j ) e.push_back({end - N + j, eve::ignore_extrema(f, l)});
    }
  }

  std::mt19937 g{42};
  auto fc = sample(firsts, cases, g);
  auto lc = sample(lasts, cases, g);
  auto ec = sample(extremas, cases, g);

  // Raw pointers captured by copy: doNotOptimizeAway clobbers memory, going through the vectors
  // would reload their data pointers on every load.
  auto load = [](auto const* c) { return eve::load[c->ignore](c->ptr, eve::as<w_t>{}); };

  auto one = [&](auto const& list)
  {
    return [&, p = list.data()]
    {
      for( std::size_t i = 0; i < cases; ++i ) ankerl::nanobench::doNotOptimizeAway(load(p + i));
    };
  };

  auto all = [&, f = fc.data(), l = lc.data(), e = ec.data()]
  {
    for( std::size_t i = 0; i < cases; ++i )
    {
      ankerl::nanobench::doNotOptimizeAway(load(f + i));
      ankerl::nanobench::doNotOptimizeAway(load(l + i));
      ankerl::nanobench::doNotOptimizeAway(load(e + i));
    }
  };

  b.batch(3 * cases).run("load[ignore]", all);
  b.batch(cases).run("load[ignore_first]", one(fc));
  b.batch(cases).run("load[ignore_last]", one(lc));
  b.batch(cases).run("load[ignore_extrema]", one(ec));
}

int main()
{
  constexpr std::ptrdiff_t page_n = 4096 / sizeof(T);
  std::vector<T, eve::aligned_allocator<T, page_n>> page(page_n, T{1});

  T const* begin = page.data();
  T const* end   = page.data() + page_n;

  // Past what the branch predictor learns.
  constexpr std::size_t cases = 1 << 20;

  ankerl::nanobench::Bench b;
  b.unit("load").minEpochIterations(10).performanceCounters(true);

  run(b, begin, end, cases);
}
