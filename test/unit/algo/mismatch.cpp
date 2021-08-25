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

TTS_CASE("Mismatch example, use previous result") {
  std::vector<int> const a{1, 2, 3, 4, 5, 6, 6, 8};
  std::vector<int> const b{1, 2, 2, 4, 5, 6, 7, 8};

  eve::algo::zip_iterator ra_rb = eve::algo::mismatch(a, b);
  TTS_EQUAL(ra_rb, eve::algo::mismatch(a, b.begin()));
  TTS_EQUAL(ra_rb, eve::algo::mismatch(a.begin(), b));

  auto& [ra, rb] = ra_rb;
  TTS_EQUAL(*ra, 3);
  TTS_EQUAL(*rb, 2);

  ++ra_rb;
  ra_rb = eve::algo::mismatch(eve::algo::as_range(ra, a.end()), rb);
  TTS_EQUAL(*ra, 6);
  TTS_EQUAL(*rb, 7);
  ++ra_rb;

  ra_rb = eve::algo::mismatch(eve::algo::as_range(ra, a.end()), rb);
  TTS_EQUAL(ra_rb, eve::algo::zip(a.end(), b.end()));
}

TTS_CASE("Mismatch example, first point not within a radius")
{
  std::vector<int>    x      { 1,   3,    -5,  10,    1};
  std::vector<int>    y      { 2,   1,     4, -10,    3};
  std::vector<double> within { 5.0, 6.0, 7.6, 10.1, 6.0};

  auto x_y = eve::algo::zip[eve::algo::common_with_types<double>](x, y);

  auto found = eve::algo::mismatch(x_y, within,
    [](eve::wide<kumi::tuple<double, double>> x_y, eve::wide<double> r) {
      auto [x, y] = x_y;
      return x * x + y * y <= r * r;
    }
  );

  auto [found_x_y, found_r] = found;
  TTS_EQUAL((found_x_y - x_y.begin()), 3);
  TTS_EQUAL(*found_x_y, (kumi::tuple{10, -10}));
  TTS_EQUAL(*found_r, 10.1);
}
