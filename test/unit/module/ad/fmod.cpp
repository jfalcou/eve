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
// Tests for eve::div
//==================================================================================================
EVE_TEST( "Check behavior of eve::div(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, T const& a1, M const& )
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;
  using eve::diff_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::fmod(vda0, a1))     , eve::fmod(a0, a1));
//  TTS_EQUAL(der(eve::fmod(vda0, a1))     , diff_1st(eve::fmod)(a0, a1));
  TTS_EQUAL(val(eve::fmod(a0, vda1))      , eve::fmod(a0, a1));
//  TTS_EQUAL(der(eve::fmod(a0, vda1)      , diff_2nd(eve::fmod)(a0, a1));

//   TTS_EQUAL(val(eve::fmod[mask](vda0, a1, a2)), eve::fmod[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::fmod[mask](vda0, a1, a2)), eve::if_else(mask, diff_1st(eve::fmod)(a0, a1, a2), eve::one));
//   TTS_EQUAL(val(eve::fmod[mask](a0, vda1, a2)), eve::fmod[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::fmod[mask](a0, vda1, a2)), eve::if_else(mask, diff_2nd(eve::fmod)(a0, a1, a2), eve::zero));
//   TTS_EQUAL(val(eve::fmod[mask](a0, a1, vda2)), eve::fmod[mask](a0, a1, a2));
//   TTS_EQUAL(der(eve::fmod[mask](a0, a1, vda2)), eve::if_else(mask, diff_3rd(eve::fmod)(a0, a1, a2), eve::zero));


};
