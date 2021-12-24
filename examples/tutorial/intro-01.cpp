//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [scalar-function]
#include <cmath>
#include <tuple>

std::tuple<float,float> to_cartesian(float rho, float theta)
{
  auto s = std::sin(theta);
  auto c = std::cos(theta);
  return { rho * c, rho * s };
}

std::tuple<float,float> to_polar(float x, float y)
{
  auto rho    = std::sqrt(x * x + y * y);
  auto theta  = std::atan2(y, x);
  return { rho, theta };
}
//! [scalar-function]

//! [simd-function]
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/atan2.hpp>

std::tuple<eve::wide<float>,eve::wide<float>> to_cartesian(eve::wide<float> rho, eve::wide<float> theta)
{
  auto s = eve::sin(theta);
  auto c = eve::cos(theta);
  return { rho * c, rho * s };
}

std::tuple<eve::wide<float>,eve::wide<float>> to_polar(eve::wide<float> x, eve::wide<float> y)
{
  auto rho    = eve::sqrt(x * x + y * y);
  auto theta  = eve::atan2(y, x);
  return { rho, theta };
}
//! [simd-function]

//! [simd-test-polar]
void check_polar()
{
  // Generates [4 4 ... 4]
  eve::wide<float> x{4};

  // Generates [1.5 3 4.5 ...]
  eve::wide<float> y{[](auto i, auto c) { return 1.5f*(i+1); }};

  std::cout << x << " " << y << "\n";

  auto[r,t] = to_polar(x,y);
  std::cout << r << " " << t << "\n";
}
//! [simd-test-polar]

//! [simd-test-cartesian]
void check_cartesian()
{
  float data[] = {1,2,3,4,5,6,7,8,9,10,11,12};

  // Generates [3 4 5 6]
  eve::wide<float, eve::fixed<4>> rho{&data[2]};

  // Generates [0 M_PI/6 M_PI/4 M_PI/2]
  eve::wide<float, eve::fixed<4>> theta{0, M_PI/6, M_PI/4, M_PI/2};

  std::cout << rho << " " << theta << "\n";

  auto[x,y] = to_cartesian(rho,theta);
  std::cout << x << " " << y << "\n";
}
//! [simd-test-cartesian]

#include "test.hpp"

TTS_CASE("Check to_polar")
{
  auto [rho,theta] = to_polar(1,1);

  TTS_ULP_EQUAL(rho   , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(theta , 0.78539819f   , 0.5);
};

TTS_CASE("Check to_cartesian")
{
  auto [x,y] = to_cartesian(2,M_PI/4);

  TTS_ULP_EQUAL(x , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(y , std::sqrt(2.f), 0.5);
};