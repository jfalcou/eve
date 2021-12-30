//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

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

//! [simd-kumi-tuple]
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>
#include <eve/product_type.hpp>

namespace simd
{
  auto to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::sqrt(x * x + y * y);
    auto theta  = eve::atan2(y, x);
    return eve::wide<kumi::tuple<float,float>>{ rho, theta };
  }
}
//! [simd-kumi-tuple]

//! [simd-transform_zip]
#include <vector>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

namespace simd
{
  auto to_polar( std::vector<float> const& xs, std::vector<float> const& ys)
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
}
//! [simd-transform_zip]

#include "test.hpp"

namespace check
{
  auto to_polar(std::vector<float> const& x, std::vector<float> const& y)
  {
    std::vector<float> rho(x.size()), theta(x.size());

    for(std::size_t i=0;i<x.size();++i)
      std::tie(rho[i], theta[i]) = ::to_polar(x[i],y[i]);

    return std::make_tuple(rho, theta);
  }
}

TTS_CASE("Check all_rhos SIMD vs Scalar")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto [scalar_rho, scalar_theta] = check::to_polar(xs,ys);
  auto [simd_rho  , simd_theta  ] = simd::to_polar(xs,ys);

  TTS_ALL_ULP_EQUAL(scalar_rho  , simd_rho  , 0.5);
  TTS_ALL_ULP_EQUAL(scalar_theta, simd_theta, 0.5);
};
