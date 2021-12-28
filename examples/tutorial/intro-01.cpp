//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

//! [scalar-function]
#include <cmath>

float rho(float x, float y)
{
  return std::sqrt(x * x + y * y);
}

float theta(float x, float y)
{
  return std::atan2(y, x);
}
//! [scalar-function]

//! [simd-function]
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/atan2.hpp>

eve::wide<float> rho(eve::wide<float> x, eve::wide<float> y)
{
  return  eve::sqrt(x * x + y * y);
}

eve::wide<float> theta(eve::wide<float> x, eve::wide<float> y)
{
  return eve::atan2(y, x);
}
//! [simd-function]

//! [simd-test]
#include <iostream>

void check_polar()
{
  eve::wide<float> x1{4};
  eve::wide<float> y1{[](auto i, auto ) { return 1.5f*(i+1); }};

  std::cout << x1 << " " << y1 << " => " << rho(x1,y1) << "\n";

  float data[] = {1.5f, 3, 4.5f, 6, 7.5f, 9, 10.5f, 12, 13.5, 15, 16.5, 18, 19.5, 21, 22.5, 24};
  eve::wide<float> y2{&data[0]};

  std::cout << x1 << " " << y2 << " => " << theta(x1,y2) << "\n";
}
//! [simd-test]

#include "test.hpp"
#include <eve/constant/sqrt_2.hpp>

TTS_CASE("Check scalar to_polar")
{
  TTS_ULP_EQUAL(rho(1,1)  , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(theta(1,1), 0.78539819f   , 0.5);
};

TTS_CASE("Check SIMD to_polar")
{
  eve::wide<float> x{1}, y{1};

  TTS_ULP_EQUAL(rho(x,y)  , eve::sqrt_2(eve::as(x))       , 0.5);
  TTS_ULP_EQUAL(theta(x,y), eve::wide<float>{0.78539819f} , 0.5);
};
