/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>

auto f(auto x, auto y)
{
  // 2*x+y*y*x
  return   eve::add(eve::mul(x, 2),  eve::cos(eve::mul(eve::sqr(y), x)));

}

auto d1f(auto x, auto y)
{
  return  2 -eve::sin(x*eve::sqr(y))*eve::sqr(y);
}

//==================================================================================================
// Tests for derivative of f
//==================================================================================================
EVE_TEST( "Check behavior of example)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(0, +10)
                              , eve::test::randoms(0, +10)
                              , eve::test::randoms(0, +10)
                              )
        )
<typename T>(T const& a0, T const& a1, T const&)
{
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;
//   using eve::diff_2nd;
//   using eve::diff_3rd;

  auto vda0 = var(a0);
//  auto vda1 = var(a1);
  TTS_ULP_EQUAL(val(f(vda0, a1))  , f(a0, a1), 0.5);
//  TTS_ULP_EQUAL(der(f(vda0, a1))  , d1f(a0, a1), 0.5);
};
