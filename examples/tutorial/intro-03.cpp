//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

namespace v1
{
//! [scalar-tuple]
#include <cmath>
#include <tuple>

std::tuple<float,float> to_polar(float x, float y)
{
  auto rho    = std::sqrt(x * x + y * y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}
//! [scalar-tuple]

//! [simd-std-tuple]
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>
#include <tuple>

std::tuple<eve::wide<float>,eve::wide<float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}
//! [simd-std-tuple]
}

namespace v2
{
//! [simd-kumi-tuple]
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>
#include <eve/product_type.hpp>

eve::wide<kumi::tuple<float,float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}
//! [simd-kumi-tuple]

//! [simd-transform_zip]
#include <cmath>
#include <vector>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

auto simd_range_to_polar( std::vector<float> const& xs, std::vector<float> const& ys)
{
  std::vector<float> rho(xs.size());
  std::vector<float> theta(xs.size());

  auto ins  = eve::views::zip(xs, ys);
  auto outs = eve::views::zip(rho, theta);

  eve::algo::transform_to ( ins, outs
                          , [](auto in) { return to_polar( get<0>(in), get<1>(in)); }
                          );

  return std::make_tuple(rho,theta);
}
//! [simd-transform_zip]
}

namespace v3
{
//! [scalar-udt]
#include <cmath>

struct polar_coords
{
  float rho, theta;
};

polar_coords to_polar(float x, float y)
{
  auto rho    = std::sqrt(x * x + y * y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}
//! [scalar-udt]
}

#include "test.hpp"

TTS_CASE("Check to_polar")
{
  auto [rho,theta] = to_polar(1,1);

  TTS_ULP_EQUAL(rho   , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(theta , 0.78539819f   , 0.5);
};
