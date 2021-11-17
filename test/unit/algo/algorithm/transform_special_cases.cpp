//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>
#include <eve/function/sqrt.hpp>

#include <eve/algo/reverse.hpp>

#include <eve/algo/swap_ranges.hpp>

TTS_CASE("eve.algo.transform different type works")
{
  std::vector<int>   in{1, 4, 9, 16};
  std::vector<short> out;
  out.resize(4);
  std::vector<short> expected{1, 2, 3, 4};

  eve::algo::transform_to(in, out, [](auto x) {
    // I know we support ints, it's a test
    auto doubles = eve::convert(x, eve::as<double>{});
    return eve::sqrt(doubles);
  });

  TTS_EQUAL(out, expected);

  // For completness
  out.clear();
  out.resize(4);
  eve::algo::transform_to(in, out, eve::sqrt);
  TTS_EQUAL(out, expected);
};

TTS_CASE("eve.algo.reverse_copy, different types")
{
  std::vector<int>   in {1, 2, 3, 4};
  std::vector<short> out (in.size());

  eve::algo::reverse_copy(in, out);

  std::vector<short> expected {4, 3, 2, 1};
  TTS_EQUAL(out, expected);
};

TTS_CASE("eve.algo.swap_ranges, different types")
{
  std::vector<int>   a {  1,  2,  3,  4};
  std::vector<short> b { -1, -2, -3, -4};

  eve::algo::swap_ranges(a, b);

  std::vector<int>   expected_a { -1, -2, -3, -4};
  std::vector<short> expected_b {  1,  2,  3,  4};

  TTS_EQUAL(a, expected_a);
  TTS_EQUAL(b, expected_b);
};
