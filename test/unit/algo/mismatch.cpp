//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/mismatch.hpp>

#include "mismatch_generic_test.hpp"

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
  TTS_EQUAL(eve::read(found_x_y), (kumi::tuple{10, -10}));
  TTS_EQUAL(eve::read(found_r), 10.1);
}

TTS_CASE("Mismatch example, zip<zip>")
{
  std::vector<float>  x { 1,      2,   3,   4};
  std::vector<float>  y { 4,      3,   2,   1};
  std::vector<double> z { 5.1,  6.1,   4.9, 5};

  auto found = eve::algo::mismatch(
    eve::algo::zip(eve::algo::zip(x, y), z),
    [](auto x_y, auto z) {
      auto [x, y] = x_y;
      return eve::convert(x + y, eve::as<double>{}) < z;
    }
  );

  TTS_EQUAL(eve::read(get<0>(found)), (kumi::tuple<float, float>{3, 2}));
  TTS_EQUAL(eve::read(get<1>(found)), 4.9);

}

EVE_TEST_TYPES("Check generic", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::mismatch_generic_test(tgt, eve::algo::mismatch,
    [](auto zip_f, auto /*zip_l*/, auto expected, auto actual) {
     TTS_EQUAL((expected - zip_f), (actual - zip_f));
  });
};
