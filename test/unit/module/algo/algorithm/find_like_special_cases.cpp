//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "unit/module/algo/udt.hpp"

#include <algorithm>
#include <vector>


TTS_CASE("eve.algo.all/any/none/find_if, empty")
{
  std::vector<int> v;
  auto p = [](auto x) { return x > 3; };

  TTS_EQUAL(
    (eve::algo::all_of(v, p)),
    (std::all_of(v.begin(), v.end(), p))
  );
  TTS_EQUAL(
    (eve::algo::any_of(v, p)),
    (std::any_of(v.begin(), v.end(), p))
  );
  TTS_EQUAL(
    (eve::algo::none_of(v, p)),
    (std::none_of(v.begin(), v.end(), p))
  );
  TTS_EQUAL(
    (eve::algo::find_if(v, p)),
    (std::find_if(v.begin(), v.end(), p))
  );
  TTS_EQUAL(
    (eve::algo::find_if_not(v, p)),
    (std::find_if_not(v.begin(), v.end(), p))
  );
  TTS_EQUAL(
    (eve::algo::find(v, 1)),
    (std::find(v.begin(), v.end(), 1))
  );
};

TTS_CASE("eve.algo.find value")
{
  std::vector<int> const v{1, 2, 3, 4, 3, 5};
  std::vector<int>::const_iterator found = eve::algo::find[eve::algo::no_aligning](v, 3);
  TTS_EQUAL((found - v.begin()), 2);

  std::vector<int>::const_iterator found_b = eve::algo::find_last[eve::algo::no_aligning](v, 3);
  TTS_EQUAL(found_b - v.begin(), static_cast<int>(v.size() - 2));
};

TTS_CASE("eve.algo.find point")
{
  std::vector<int> x{1, 2, 3, 4};
  std::vector<int> y{0, 0, 1, 1};

  auto as_points = eve::algo::views::convert(
    eve::algo::views::zip(x, y), eve::as<udt::point2D>{});

  auto found = eve::algo::find_if(as_points,
    [](eve::wide<udt::point2D> points) { return get_y(points) != 0; });

  TTS_EQUAL(eve::read(found), (udt::point2D{3, 1}));
};

TTS_CASE("eve.algo.find_if not in radius")
{
  std::vector<int> x {1, -1, 2, -10};
  std::vector<int> y {0,  1, 2,   5};

  int r = 6;

  auto within_radius = [r_square = r * r](auto x_y) {
    auto [x, y] = x_y;
    return x * x + y * y <= r_square;
  };

  auto found = eve::algo::find_if_not(eve::algo::views::zip(x, y), within_radius);
  TTS_EQUAL(eve::read(found), (kumi::tuple{-10, 5}));
};

TTS_CASE("eve.algo.mismatch example, use previous result") {
  std::vector<int> const a{1, 2, 3, 4, 5, 6, 6, 8};
  std::vector<int> const b{1, 2, 2, 4, 5, 6, 7, 8};

  eve::algo::views::zip_iterator ra_rb = eve::algo::mismatch(a, b);
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
  TTS_EQUAL(ra_rb, eve::algo::views::zip(a.end(), b.end()));
};

TTS_CASE("eve.algo.mismatch example, first point not within a radius")
{
  std::vector<int>    x      { 1,   3,    -5,  10,    1};
  std::vector<int>    y      { 2,   1,     4, -10,    3};
  std::vector<double> within { 5.0, 6.0, 7.6, 10.1, 6.0};

  auto x_y = eve::algo::views::zip[eve::algo::common_with_types<double>](x, y);

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
};

TTS_CASE("eve.algo.mismatch example, zip<zip>")
{
  std::vector<float>  x { 1,      2,   3,   4};
  std::vector<float>  y { 4,      3,   2,   1};
  std::vector<double> z { 5.1,  6.1,   4.9, 5};

  auto found = eve::algo::mismatch(
    eve::algo::views::zip(eve::algo::views::zip(x, y), z),
    [](auto x_y, auto z) {
      auto [x, y] = x_y;
      return eve::convert(x + y, eve::as<double>{}) < z;
    }
  );

  TTS_EQUAL(eve::read(get<0>(found)), (kumi::tuple<float, float>{3, 2}));
  TTS_EQUAL(eve::read(get<1>(found)), 4.9);
};

TTS_CASE("eve.algo.equal/mismatch by key")
{
  std::vector<int        > k_1 {1,     2,   3,   4};
  std::vector<std::int8_t> v_1 {'a', 'b', 'c', 'd'};
  auto map_1 = eve::algo::views::zip(k_1, v_1);

  std::vector<int        > k_2 = k_1;
  std::vector<double     > v_2 = {0.1, 0.2, 0.3, 0.4};
  auto map_2 = eve::algo::views::zip(k_2, v_2);

  auto compare_key = [](auto m1, auto m2) { return get<0>(m1) == get<0>(m2); };

  // do equal
  {
    TTS_EXPECT(eve::algo::equal(map_1, map_2, compare_key));

    auto mmatch = eve::algo::mismatch(map_1, map_2, compare_key);
    TTS_EQUAL(get<0>(mmatch), map_1.end());
  }

  // do not equal
  {
    int offset = 2;
    k_2[offset] = -1;

    TTS_EXPECT_NOT(eve::algo::equal(map_1, map_2, compare_key));

    auto mmatch = eve::algo::mismatch(map_1, map_2, compare_key);
    TTS_NOT_EQUAL(get<0>(mmatch), map_1.end());
    TTS_EQUAL    (get<0>(mmatch), map_1.begin() + offset);
  }
};
