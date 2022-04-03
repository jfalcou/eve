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
// Tests for eve::rec
//==================================================================================================
EVE_TEST( "Check behavior of eve::rec(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::rec(vda0))      , eve::rec(a0));
  TTS_EQUAL(val(eve::rec[mask](vda0)), eve::rec[mask](a0));
  TTS_ULP_EQUAL(der(eve::rec(vda0))      , diff(eve::rec)(a0), 1.0);
  TTS_EQUAL(der(eve::rec[mask](vda0)), eve::if_else(mask, diff(eve::rec)(a0), eve::one));
};
