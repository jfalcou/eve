//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

//! [scalar-loop]
#include <vector>
#include <cmath>
#include <tuple>

std::tuple<float,float> to_polar(float x, float y)
{
  auto rho    = std::sqrt(x * x + y * y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}

auto to_scalar_polar(std::vector<float> const& x, std::vector<float> const& y)
{
  std::vector<float> rho(x.size()), theta(x.size());

  for(std::size_t i=0;i<x.size();++i)
  {
    auto[r,t] = to_polar(x[i],y[i]);
    rho[i]    = r;
    theta[i]  = t;
  }

  return std::make_tuple(rho, theta);
}
//! [scalar-loop]

//! [scalar-loop-test]
#include <iostream>

void check_scalar()
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto[rs,ts] = to_scalar_polar(xs,ys);
  for(auto r : rs) std::cout << r << " ";
  std::cout << "\n";

  for(auto t : ts) std::cout << t << " ";
  std::cout << "\n";
}
//! [scalar-loop-test]

//! [simd-loop]
#include <eve/wide.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/atan2.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/store.hpp>
#include <tuple>

std::tuple<eve::wide<float>,eve::wide<float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}

auto to_simd_polar(std::vector<float> const& x, std::vector<float> const& y)
{
  using w_t = eve::wide<float>;
  std::vector<float> rho(x.size()), theta(x.size());

  for(std::size_t i=0;i<x.size();i += w_t::size())
  {
    auto[r,t] = to_polar(w_t(&x[i]),w_t(&y[i]));
    eve::store(r, &rho[i]   );
    eve::store(t, &theta[i] );
  }

  return std::make_tuple(rho, theta);
}
//! [simd-loop]

//! [simd-loop-exact]
auto to_simd_polar_exact(std::vector<float> const& x, std::vector<float> const& y)
{
  using w_t = eve::wide<float>;
  std::vector<float> rho(x.size()), theta(x.size());

  auto last_simd = eve::align(x.size(), eve::under{w_t::size()});

  for(std::size_t i=0;i<last_simd;i += w_t::size())
  {
    auto[r,t] = to_polar(w_t(&x[i]),w_t(&y[i]));
    eve::store(r, &rho[i]   );
    eve::store(t, &theta[i] );
  }

  for(std::size_t i=last_simd;i<x.size();i++)
  {
    auto[r,t] = to_polar(x[i],y[i]);
    rho[i]   = r;
    theta[i] = t;
  }

  return std::make_tuple(rho, theta);
}
//! [simd-loop-exact]

#include "test.hpp"

TTS_CASE("Check to_polar SIMD vs Scalar - exact size")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1,-0.8,-0.6,-0.4,-0.2   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1,0.,0.1,0.2,0.5 };

  auto scalar_outs  = to_scalar_polar(xs,ys);
  auto simd_outs    = to_simd_polar(xs,ys);

  TTS_ALL_ULP_EQUAL(get<0>(scalar_outs) , get<0>(simd_outs), 1);
  TTS_ALL_ULP_EQUAL(get<1>(scalar_outs) , get<1>(simd_outs), 1);
};

TTS_CASE("Check to_polar SIMD vs Scalar - arbitrary size")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto scalar_outs  = to_scalar_polar(xs,ys);
  auto simd_outs    = to_simd_polar_exact(xs,ys);

  TTS_ALL_ULP_EQUAL(get<0>(scalar_outs) , get<0>(simd_outs), 1);
  TTS_ALL_ULP_EQUAL(get<1>(scalar_outs) , get<1>(simd_outs), 1);
};
