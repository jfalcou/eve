//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <algorithm>
#include <functional>
#include <vector>

TTS_CASE("eve.algo.reduce sum complex numbers")
{
  std::vector<float> real = {0.0, 0.1, 0.2, 0.3};
  std::vector<float> img  = {0.0, -0.1, -0.2, -0.3};

  using cmplx = kumi::tuple<float, float>;

  auto plus = [](eve::like<cmplx> auto x, eve::like<cmplx> auto y)
  {
    get<0>(x) += get<0>(y);
    get<1>(x) += get<1>(y);
    return x;
  };

  auto [re, im] = eve::algo::reduce(
      eve::algo::views::zip(real, img), std::pair {plus, cmplx {0.0, 0.0}}, cmplx {1, -1});

  TTS_RELATIVE_EQUAL(re, 1.6, 0.0001);
  TTS_RELATIVE_EQUAL(im, -1.6, 0.0001);
};

TTS_CASE("eve.algo.inclusive_scan a vector")
{
  std::vector<int> v {0, 1, 2, 3, 4};

  std::vector<int> expected(v.size());
  std::inclusive_scan(v.begin(), v.end(), expected.begin(), std::plus<> {}, -1);

  eve::algo::inclusive_scan_inplace(v, -1);
  TTS_EQUAL(v, expected);
};

TTS_CASE("eve.algo.inclusive_scan complex numbers")
{
  std::vector<float> real = {0.0, 0.1, 0.2, 0.3};
  std::vector<float> img  = {0.0, -0.1, -0.2, -0.3};

  using cmplx = kumi::tuple<float, float>;

  auto plus = [](eve::like<cmplx> auto x, eve::like<cmplx> auto y)
  {
    get<0>(x) += get<0>(y);
    get<1>(x) += get<1>(y);
    return x;
  };

  std::vector<float> real_copy = real;
  std::vector<float> img_copy  = img;

  kumi::tuple<float, float> init {0.0, 0.0};

  eve::algo::inclusive_scan_to(eve::algo::views::zip(real, img),
                               eve::algo::views::zip(real_copy, img_copy),
                               std::pair {plus, eve::zero},
                               init);

  eve::algo::inclusive_scan_inplace(
      eve::algo::views::zip(real, img), std::pair {plus, eve::zero}, init);

  std::vector<float> expected_real = {0.0, 0.1, 0.3, 0.6};
  std::vector<float> expected_img  = {0.0, -0.1, -0.3, -0.6};
  TTS_EQUAL(expected_real, real);
  TTS_EQUAL(expected_img, img);

  TTS_EQUAL(expected_real, real_copy);
  TTS_EQUAL(expected_img, img_copy);
};

TTS_CASE("eve.algo.transform_reduce_simple")
{
  std::vector<float> v {1.0f, 2.0f, 3.0f};

  auto r = eve::algo::transform_reduce(
      v, [](auto x) { return x + x; }, 0.0);
  TTS_EQUAL(r, 12.0);
  TTS_TYPE_IS(decltype(r), double);
};

TTS_CASE("eve.algo.transform_reduce_types")
{
  std::vector<std::int8_t> v {1, 2, 3};

  {
    auto r = eve::algo::transform_reduce(
        v, [](eve::wide<std::int8_t> x) { return x + x; }, std::int8_t {0});
    TTS_TYPE_IS(decltype(r), std::int8_t);
  }
  {
    using N = eve::fixed<eve::expected_cardinal_v<std::int16_t>>;
    auto r  = eve::algo::transform_reduce(
        v, [](eve::wide<std::int8_t, N> x) { return x + x; }, std::int16_t {0});
    TTS_TYPE_IS(decltype(r), std::int16_t);
  }
  {
    using N = eve::fixed<eve::expected_cardinal_v<std::int16_t>>;
    // return type of map does not matter
    auto r = eve::algo::transform_reduce(
        v,
        [](eve::wide<std::int8_t, N> x) { return eve::convert(x + x, eve::as<std::int32_t> {}); },
        std::int16_t {0});
    TTS_TYPE_IS(decltype(r), std::int16_t);
  }
};

TTS_CASE("eve.algo.reduce, stateful reduce")
{
  std::vector v {1, 2, 3};

  TTS_EQUAL(6,
            eve::algo::reduce(v,
                              std::pair {[_ = 3](auto x, auto y)
                                         {
                                           (void)_;
                                           return x + y;
                                         },
                                         eve::zero},
                              0));
};

TTS_CASE("eve.algo.transform_reduce, stateful map/reduce")
{
  int coeff = 2;

  std::vector v {1, 2, 3};

  TTS_EQUAL(12,
            eve::algo::transform_reduce(
                v,
                [coeff](auto x) { return x * coeff; },
                std::pair {[_ = coeff](auto x, auto y)
                           {
                             (void)_;
                             return x + y;
                           },
                           eve::zero},
                0));
};
