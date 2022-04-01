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
// Tests for eve::rsqrt
//==================================================================================================
EVE_TEST( "Check behavior of eve::rsqrt(eve::wide)"
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
  TTS_ULP_EQUAL(val(eve::rsqrt(vda0))      , eve::rsqrt(a0), 0.5);
  TTS_ULP_EQUAL(val(eve::rsqrt[mask](vda0)), eve::rsqrt[mask](a0), 0.5);
  TTS_ULP_EQUAL(der(eve::rsqrt(vda0))      , diff(eve::rsqrt)(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::rsqrt[mask](vda0)), eve::if_else(mask, diff(eve::rsqrt)(a0), eve::one), 0.5);
};
