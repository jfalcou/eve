//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <tuple>
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/atan2.hpp>

std::tuple<float,float> to_polar(float x, float y)
{
  auto rho    = std::sqrt(x * x + y * y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}

std::tuple<eve::wide<float>,eve::wide<float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}

//! [std-transform]
#include <cmath>
#include <vector>
#include <algorithm>

auto std_algo(std::vector<float> const& in)
{
  std::vector<float> out(in.size());

  std::transform( in.begin(), in.end(), out.begin()
                , [](float x) { return std::exp(1.f/x); }
                );
  return out;
}
//! [std-transform]

//! [std-transform-range]
#include <cmath>
#include <vector>
#include <algorithm>

auto std_algo_range(std::vector<float> const& in)
{
  std::vector<float> out(in.size());

  std::ranges::transform( in, out.begin()
                        , [](float x) { return std::exp(1.f/x); }
                        );
  return out;
}
//! [std-transform-range]

//! [simd-transform]
#include <vector>
#include <eve/algo/transform.hpp>
#include <eve/function/exp.hpp>

auto simd_algo_range(std::vector<float> const& in)
{
  std::vector<float> out(in.size());

  eve::algo::transform_to ( in, out
                          , [](eve::wide<float> x) { return eve::exp(1.f/x); }
                          );
  return out;
}
//! [simd-transform]

//! [simd-tuple]
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>
#include <eve/product_type.hpp>

auto to_polar2(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return eve::wide<kumi::tuple<float,float>>{ rho, theta };
}
//! [simd-tuple]

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
                          , [](auto in) { return to_polar2( get<0>(in), get<1>(in)); }
                          );

  return std::make_tuple(rho,theta);
}
//! [simd-transform_zip]

//#include "test.hpp"
