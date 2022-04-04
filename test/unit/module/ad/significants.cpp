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
// Tests for eve::nextafter
//==================================================================================================
EVE_TEST( "Check behavior of eve::nextafter(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::ramp(1, 1)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::var;
  using eve::val;
  using eve::der;

  auto vda0 = var(a0);
  auto ia1 = eve::int_(a1);
  TTS_ULP_EQUAL(eve::significants(vda0, ia1)  , eve::significants(a0, ia1), 0.5);

};
