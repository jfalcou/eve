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

//==================================================================================================
// Tests for eve::add
//==================================================================================================
EVE_TEST( "Check behavior of eve::pow_abs(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;
  using eve::diff_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::pow_abs(vda0, a1))      , eve::pow_abs(a0, a1));
  TTS_EQUAL(der(eve::pow_abs(vda0, a1))      , diff_1st(eve::pow_abs)(a0, a1));
  TTS_EQUAL(val(eve::pow_abs(a0, vda1))      , eve::pow_abs(a0, a1));
  TTS_EQUAL(der(eve::pow_abs(a0, vda1))      , diff_2nd(eve::pow_abs)(a0, a1));
};
