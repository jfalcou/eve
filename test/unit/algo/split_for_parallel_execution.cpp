//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/split_for_parallel_execution.hpp>

#include <eve/algo/as_range.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <eve/memory/aligned_allocator.hpp>

#include <algorithm>

// Checks that the step is fully aligned
struct type_test
{
  void first_step(auto) {}

  template <eve::algo::partially_aligned_iterator I>
  void step(eve::algo::as_range<I, I>) {}

  void last_step(auto) {}
};

struct values_test
{
  int const* start;

  std::vector<kumi::tuple<int, int>> res;

  auto push(auto r) {
    int f = r.begin().unaligned().ptr - start;
    int l = r.end().unaligned().ptr - start;
    res.push_back(kumi::tuple{f, l});
  }

  void first_step(auto r)
  {
    start = r.begin().unaligned().ptr;
    push(r);
  }

  void step(auto r)
  {
    push(r);
  }

  void last_step(auto r)
  {
    push(r);
  }
};

auto test_values(
  auto&& rng,
  int groups, int min_size,
  std::vector<kumi::tuple<int, int>> expected
)
{
  values_test vt;
  int count = eve::algo::split_for_parallel_execution(rng, vt, groups, min_size);
  TTS_EQUAL(expected, vt.res);

  int expected_count = std::count_if(expected.begin(), expected.end(),
    [](auto p) { return get<0>(p) != get<1>(p); });

  TTS_EQUAL(expected_count, count);
}

TTS_CASE("eve.algo.split_for_parallel_execution, types")
{
  std::vector<int> v;
  eve::algo::split_for_parallel_execution(v, type_test{}, 1, 1);

  TTS_PASS("types check out");
}

TTS_CASE("eve.algo.split_for_parallel_execution, values")
{
  using a_v = std::vector<int, eve::aligned_allocator<int, eve::fixed<16>>>;

  // empty
  {
    a_v v;

    test_values(v, 1, 1,
      { {0, 0}, {0, 0} }
    );
  }
  // align middle
  {
    a_v v (100u, 0);

    test_values(v, 2, 45,
      { {0, 64}, {64, 100} }
    );
  }
  // two chunks middle
  {
    a_v v (200u, 0);

    test_values(v, 4, 50,
      { {0, 64}, {64, 112}, {112, 160}, {160, 200} }
    );
  }
  // too small of a range
  {
    std::vector<int> v(1000u, 0);

    test_values(v, 3, 10'000,
      { {0, 1000}, {1000, 1000} }
    );
  }
}
