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
// Tests for eve::acospi
//==================================================================================================
EVE_TEST( "Check behavior of eve::acospi(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1, +1)
                              )
        )
<typename T>(T const& a0)
{
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::acospi(vda0))      , eve::acospi(a0));
  TTS_EQUAL(der(eve::acospi(vda0))      , diff(eve::acospi)(a0));
};
