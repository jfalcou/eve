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
// Tests for eve::average
//==================================================================================================
EVE_TEST( "Check behavior of eve::average(eve::wide)"
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
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::average(vda0, a1, a2))      , eve::average(a0, a1, a2));
  TTS_EQUAL(val(eve::average[mask](vda0, a1)), eve::average[mask](a0, a1));
  TTS_EQUAL(der(eve::average(vda0, a1, a2))      , diff(eve::average)(a0, a1, a2));
  TTS_EQUAL(der(eve::average[mask](vda0, a1)), diff(eve::average[mask])(a0, a1));
};
