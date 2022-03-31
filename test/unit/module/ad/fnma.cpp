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
// Tests for eve::fnma
//==================================================================================================
EVE_TEST( "Check behavior of eve::fnma(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& mask)
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
  TTS_EQUAL(val(eve::fnma(vda0, a1, a2))      , eve::fnma(a0, a1, a2));
  TTS_EQUAL(der(eve::fnma(vda0, a1, a2))      , diff_1st(eve::fnma)(a0, a1, a2));
  TTS_EQUAL(val(eve::fnma(a0, vda1, a2))      , eve::fnma(a0, a1, a2));
  TTS_EQUAL(der(eve::fnma(a0, vda1, a2))      , diff_2nd(eve::fnma)(a0, a1, a2));
  TTS_EQUAL(val(eve::fnma(a0, a1, vda2))      , eve::fnma(a0, a1, a2));
  TTS_EQUAL(der(eve::fnma(a0, a1, vda2))      , diff_3rd(eve::fnma)(a0, a1, a2));


  TTS_EQUAL(val(eve::fnma[mask](vda0, a1, a2)), eve::fnma[mask](a0, a1, a2));
  TTS_EQUAL(der(eve::fnma[mask](vda0, a1, a2)), diff_1st(eve::fnma[mask])(a0, a1, a2));
  TTS_EQUAL(val(eve::fnma[mask](a0, vda1, a2)), eve::fnma[mask](a0, a1, a2));
  TTS_EQUAL(der(eve::fnma[mask](a0, vda1, a2)), diff_2nd(eve::fnma[mask])(a0, a1, a2));
  TTS_EQUAL(val(eve::fnma[mask](a0, a1, vda2)), eve::fnma[mask](a0, a1, a2));
  TTS_EQUAL(der(eve::fnma[mask](a0, a1, vda2)), diff_3rd(eve::fnma[mask])(a0, a1, a2));
};
