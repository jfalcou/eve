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
  auto rho    = std::hypot(x, y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}
//! [scalar-tuple]

//! [simd-std-tuple]
#include <eve/wide.hpp>
#include <eve/module/math.hpp>
#include <tuple>

std::tuple<eve::wide<float>,eve::wide<float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::hypot(x, y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}
//! [simd-std-tuple]

//! [simd-kumi-tuple]
#include <eve/module/math.hpp>
#include <eve/product_type.hpp>

namespace simd
{
  auto to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::hypot(x, y);
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

  auto scalar_outs  = check::to_polar(xs,ys);
  auto simd_outs    = simd::to_polar(xs,ys);

  TTS_ALL_ULP_EQUAL(get<0>(scalar_outs) , get<0>(simd_outs), 1);
  TTS_ALL_ULP_EQUAL(get<1>(scalar_outs) , get<1>(simd_outs), 1);
};
