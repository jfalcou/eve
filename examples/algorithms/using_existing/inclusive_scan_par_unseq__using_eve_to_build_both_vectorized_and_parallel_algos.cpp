//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

// In this example we are going to have a look at the problem from
// this https://stackoverflow.com/q/10587598/5021064
//
// The solution by @Zbozon was the basis of our inclusive_scan implementation.
//
// eve itself does not deal with threading however it's a good building block.

// The main idea:
//   * split the computation into chunks
//   * scan each chunk in parallel
//   * each thread writes the overall sum into a vector
//   * scan a vector of sums on one thread
//   * each thread applies a previous sum to each part

// NOTE: please don't do threading like we do, it's very very bad.
//       Ideally you want some reasonable tasking system.
//       Maybe: https://stlab.cc/ ?

// NOTE: supporting SOA here is possible but it makes the solution
//       much more complicated.

#include <eve/algo/inclusive_scan.hpp>
#include <eve/algo/transform.hpp>

#include <eve/memory/aligned_ptr.hpp>

#include <future>
#include <thread>

// -------------------------
// typedefs

// The example was about floats
using T = float;

// We are going to use alignment of at least 64 bytes so that
// threads don't touch each other's cache lines.

using cache_line_n = eve::fixed<64 / sizeof(T)>;
using aptr         = eve::aligned_ptr<T, cache_line_n>;

using uptr_range   = eve::algo::as_range<T*, T*>;
using aptr_range   = eve::algo::as_range<aptr, aptr>;

// -------------------------
// inclusive_scan/add_to_each
//
// Wrappers around eve algorithms, that will likely not be inlined.
//
//
// TODO: think, maybe we should return the sum from `eve::algo::inclusive_scan`
//       since we don't return the output iterator anyways?
struct
{
  // boundary version
  float operator()(uptr_range r, T init) const
  {
    if (r.begin() == r.end()) return init;
    eve::algo::inclusive_scan_inplace(r, init);
    return *(r.end() - 1);
  }

  // middle version
  float operator()(aptr_range r) const
  {
    if (r.begin() == r.end()) return 0.0f;
    eve::algo::inclusive_scan_inplace(r, 0.0f);
    return *(r.end().get() - 1);
  }

} inline constexpr inclusive_scan;

struct
{
  void operator()(uptr_range r, T v) const
  {
    eve::algo::transform_inplace(r, [v](auto x) { return x + v; });
  }

  void operator()(aptr_range r, T v) const
  {
    eve::algo::transform_inplace(r, [v](auto x) { return x + v; });
  }
} inline constexpr add_to_each;


// -----------------------------------
// subranges_split
//
// First and last chunks will be not well aligned, while the middle chunks
// are aligned from both sides.
//
// NOTE: this `split` is fairly difficult to test properly,
//       no guarntees that it's bug free.

struct subranges_split_t
{
  uptr_range              first;
  std::vector<aptr_range> middle;
  uptr_range              last;

  subranges_split_t():
    first(nullptr, nullptr),
    middle(),
    last(nullptr, nullptr)
  {}
};

subranges_split_t subranges_split(uptr_range r,
                                  std::ptrdiff_t subrange_count,
                                  std::ptrdiff_t rough_min_size) {
  T* f = r.begin();
  T* l = r.end();

  subranges_split_t res;

  if( l - f <= rough_min_size )
  {
    res.first = {f, l};
    return res;
  }

  // Select chunk size:
  // either based on subrange count or rough min size but always divisible by cacheline
  // We round up.
  std::ptrdiff_t chunk_size = std::max((l - f) / subrange_count, rough_min_size);
  chunk_size += cache_line_n{}() - chunk_size % cache_line_n{}();

  aptr f1 = eve::previous_aligned_address(f + chunk_size, cache_line_n{});
  res.first = {f, f1.get()};

  while (l - f1 > chunk_size) {
    aptr f2 = f1 + chunk_size;
    res.middle.emplace_back(f1, f2);
    f1 = f2;
  }

  res.last = {f1.get(), l};

  return res;
}

// --------------------------------
// par unseq scan
//
// NOTE: std::async/std::future are placeholders for your tasking system.

// 16 pages per thread, completly out of the blue.
constexpr std::ptrdiff_t job_size = 4096 * 16 / sizeof(T);

namespace _inclusive_scan_par_unseq
{
  // Run inclusive scan in each part.
  // Returns the sums of each part in a vector.
  // Alternatively, we could not allocate the sums vector
  // but then we couldn't run a vectorized scan on them.
  //
  // Also some logic would be more difficult.
  std::vector<T> scan_step(subranges_split_t const& subranges, T init)
  {
    std::vector<std::future<T>> async_work;

    // First and middle chunk schedule on different threads.
    // `std::async` is not great and is used as a stand in for a real tasking system used.
    async_work.push_back(std::async(inclusive_scan, subranges.first, init));

    for (auto m : subranges.middle) {
      async_work.push_back(std::async(inclusive_scan, m));
    }

    // Compute last chunk on the main thread.
    // Alternatively this could've been also scheduled asyncronously,
    // and the caller could continue straight away.
    inclusive_scan(subranges.last, T(0));

    std::vector<T> res (subranges.middle.size() + 1);

    // when all. Due to using std::future is blocking. Ideally - should be async.
    std::transform(async_work.begin(), async_work.end(), res.begin(),
                   [](auto& f) { return f.get(); });

    return res;
  }

  void add_previous_sum_step(subranges_split_t const& subranges, std::vector<T> const& sums)
  {
    std::vector<std::future<void>> async_work;

    for (std::size_t i = 0; i != subranges.middle.size(); ++i) {
      async_work.push_back(std::async(add_to_each, subranges.middle[i], sums[i]));
    }

    // add to last chunk on the main thread
    add_to_each(subranges.last, sums.back());

    // when all, should be asyncrunous in a normal tasking system.
    for (auto& f : async_work) f.get();
  }
}


void inclusive_scan_par_unseq(uptr_range r, T init)
{
  // First we split into subranges that we are going to process in parallel
  auto subranges = subranges_split(r, (std::ptrdiff_t)std::thread::hardware_concurrency(), job_size);

  // Scan each subrange
  std::vector<T> sums = _inclusive_scan_par_unseq::scan_step(subranges, init);

  // scan sums
  inclusive_scan(uptr_range{sums.data(), sums.data() + sums.size()}, 0.0);

  // add a previous sum to each chunk
  _inclusive_scan_par_unseq::add_previous_sum_step(subranges, sums);
}

// -----------------------

#include "test.hpp"

#include <eve/memory/aligned_allocator.hpp>

TTS_CASE("subranges_split") {
  using a_v = std::vector<T, eve::aligned_allocator<T, cache_line_n>>;

  using idx_pair = kumi::tuple<std::ptrdiff_t, std::ptrdiff_t>;

  auto split_to_ints = [](subranges_split_t split) {
    T* base = split.first.begin();

    std::vector<idx_pair> res;

    auto push_range = [&](auto r) mutable {
      if (r.begin() == r.end()) return;

      res.push_back(idx_pair{r.begin() - base, r.end() - base});
    };

    push_range(split.first);

    for (auto r : split.middle) push_range(r);

    push_range(split.last);

    return res;
  };

  auto test = [&](auto&& r, int group_count, int group_size, std::vector<idx_pair> expected)
  {
    auto split = subranges_split(
      eve::algo::as_range(r.data(), r.data() + r.size()),
      group_count, group_size);
    TTS_EQUAL(expected, split_to_ints(split));
  };

  // empty
  {
    a_v v;
    test(v, 1, 1, {});
  }

  // align middle
  {
    a_v v (100u, 0);

    test(v, 2, 45,
      { {0, 64}, {64, 100} }
    );
  }

  // two chunks middle
  {
    a_v v (200u, 0);

    test(v, 4, 50,
      { {0, 64}, {64, 128}, {128, 192}, {192, 200} }
    );
  }
  // too small of a range
  {
    std::vector<T> v(1000u, 0);

    test(v, 3, 10'000,
      { {0, 1000} }
    );
  }

  // giant range
  {
    std::size_t size = job_size * 16;
    std::vector<T> v (size, T(15));
    subranges_split(uptr_range(v.data(), v.data() + size),
      (std::ptrdiff_t)std::thread::hardware_concurrency(), job_size);
  }

}

TTS_CASE("inclusive_scan")
{
  std::vector<T> v;
  TTS_EQUAL(inclusive_scan(eve::algo::as_range(v.data(), v.data() + v.size()), T{3}),
            T{3});
}

TTS_CASE("inclusive_scan_par_unseq")
{
  {
      std::vector<T> v;
      inclusive_scan_par_unseq(uptr_range(v.data(), v.data() + v.size()), T(0));
  }

  {
    std::size_t size = job_size * 16;
    std::vector<T> v (size, T(15));
    std::vector<T> expected(size, T(0));
    eve::algo::inclusive_scan_to(v, expected, T(5));
    inclusive_scan_par_unseq(uptr_range(v.data(), v.data() + v.size()), T(5));
    TTS_EQUAL(expected, v);
  }
}
