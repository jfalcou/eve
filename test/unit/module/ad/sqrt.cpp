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
// Tests for eve::sqrt
//==================================================================================================
EVE_TEST( "Check behavior of eve::sqrt(eve::wide)"
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
  TTS_ULP_EQUAL(val(eve::sqrt(vda0))      , eve::sqrt(a0), 0.5);
  TTS_ULP_EQUAL(val(eve::sqrt[mask](vda0)), eve::sqrt[mask](a0), 0.5);
  TTS_ULP_EQUAL(der(eve::sqrt(vda0))      , diff(eve::sqrt)(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::sqrt[mask](vda0)), eve::if_else(mask, diff(eve::sqrt)(a0), eve::one), 0.5);
};
