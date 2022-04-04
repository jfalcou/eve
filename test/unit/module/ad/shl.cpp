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
// Tests for eve::shl
//==================================================================================================
EVE_TEST( "Check behavior of eve::shl(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::ramp(0, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const&  )
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;

  auto vda0 = var(a0);
  auto ia1 = eve::int_(a1);
  TTS_EQUAL(eve::shl(vda0, ia1)  , eve::shl(a0, ia1));

//  TTS_EQUAL(eve::shl[mask](vda0, a1)  , eve::shl[mask](a0, a1));
};
