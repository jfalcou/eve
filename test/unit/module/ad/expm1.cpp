//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>

//==================================================================================================
// Tests for eve::expm1
//==================================================================================================
EVE_TEST( "Check behavior of eve::expm1(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0)
{
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::expm1(vda0))      , eve::expm1(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::expm1(vda0))      , diff(eve::expm1)(a0), 0.5);
};
