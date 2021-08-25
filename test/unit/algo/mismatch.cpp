//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/mismatch.hpp>

#include <vector>

TTS_CASE("Mismatch basic") {
  std::vector<int> a{1, 2, 3, 4};
  std::vector<int> b{1, 2, 2, 4};

  auto ra_rb = eve::algo::mismatch(a, b);
  TTS_EQUAL(ra_rb, eve::algo::mismatch(a, b.begin()));
  TTS_EQUAL(ra_rb, eve::algo::mismatch(a.begin(), b));

  auto [ra, rb] = ra_rb;
  TTS_EQUAL(*ra, 3);
  TTS_EQUAL(*rb, 2);
}
