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
// Tests for eve::floor
//==================================================================================================
EVE_TEST( "Check behavior of eve::floor(eve::wide)"
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
  TTS_EQUAL(val(eve::floor(vda0))      , eve::floor(a0));
  TTS_EQUAL(val(eve::floor[mask](vda0)), eve::floor[mask](a0));
  TTS_EQUAL(der(eve::floor(vda0))      , diff(eve::floor)(a0));
  TTS_EQUAL(der(eve::floor[mask](vda0)), eve::if_else(mask, diff(eve::floor)(a0), eve::one));
};
