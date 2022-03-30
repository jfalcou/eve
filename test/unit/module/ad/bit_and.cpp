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
// Tests for eve::add
//==================================================================================================
EVE_TEST( "Check behavior of eve::add(eve::wide)"
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
  TTS_EQUAL(val(eve::bit_and(vda0, a1, a2))      , eve::bit_and(a0, a1, a2));
  TTS_EQUAL(val(eve::bit_and[mask](vda0, a1)), eve::bit_and[mask](a0, a1));
  TTS_EQUAL(der(eve::bit_and(vda0, a1, a2))      , diff(eve::bit_and)(a0, a1, a2));
  TTS_EQUAL(der(eve::bit_and[mask](vda0, a1)),  diff(eve::bit_and[mask])(a0, a1));
};
