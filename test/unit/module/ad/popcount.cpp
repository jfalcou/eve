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
// Tests for eve::popcount
//==================================================================================================
EVE_TEST( "Check behavior of eve::popcount(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& )
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(eve::popcount(vda0)      , eve::popcount(a0));
//   TTS_EQUAL(val(eve::popcount[mask](vda0)), eve::popcount[mask](a0));
//   TTS_EQUAL(der(eve::popcount(vda0))      , diff(eve::popcount)(a0));
//   TTS_EQUAL(der(eve::popcount[mask](vda0)), eve::if_else(mask, diff(eve::popcount)(a0), eve::one));
};
