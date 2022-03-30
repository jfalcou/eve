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
// Tests for eve::absmin
//==================================================================================================
EVE_TEST( "Check behavior of eve::absmin(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;
  using eve::diff_2nd;
  using eve::diff_3rd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  auto vda2 = var(a2);

  TTS_EQUAL(val(eve::absmin(vda0, a1, a2))  , eve::absmin(a0, a1, a2));
  TTS_EQUAL(der(eve::absmin(vda0, a1, a2))  , diff_1st(eve::absmin)(a0, a1, a2));
  TTS_EQUAL(val(eve::absmin(a0, vda1, a2))  , eve::absmin(a0, a1, a2));
  TTS_EQUAL(der(eve::absmin(a0, vda1, a2))  , diff_2nd(eve::absmin)(a0, a1, a2));
  TTS_EQUAL(val(eve::absmin(a0, a1, vda2))  , eve::absmin(a0, a1, a2));
  TTS_EQUAL(der(eve::absmin(a0, a1, vda2))  , diff_3rd(eve::absmin)(a0, a1, a2));
};
