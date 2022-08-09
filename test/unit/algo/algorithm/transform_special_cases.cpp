//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>

#include <eve/algo/reverse.hpp>
#include <eve/algo/swap_ranges.hpp>

#include <eve/algo/fill.hpp>

#include <eve/views/zip.hpp>

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

TTS_CASE("eve.algo.fill, tuples")
{
  std::vector<int>          a {1, 2, 3};
  std::vector<std::uint8_t> b {1, 2, 3};
  std::vector<double>       c {1, 2, 3};

  std::vector<int>           expected_a{ 0, 0, 0 };
  std::vector<std::uint8_t>  expected_b{ 1, 1, 1 };
  std::vector<double>        expected_c{ 2.0, 2.0, 2.0 };


  eve::algo::fill(eve::views::zip(a, b, c), kumi::tuple{0, std::uint8_t{1}, 2.0});
  TTS_EQUAL(a, expected_a);
  TTS_EQUAL(b, expected_b);
  TTS_EQUAL(c, expected_c);
};
