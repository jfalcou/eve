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
                              , eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const& mask )
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff_1st;
  using eve::diff_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::nextafter(vda0, a1))  , eve::nextafter(a0, a1));
  TTS_EQUAL(val(eve::nextafter(a0, vda1))  , eve::nextafter(a0, a1));

  TTS_EQUAL(val(eve::nextafter[mask](vda0, a1))  , eve::nextafter[mask](a0, a1));
  TTS_EQUAL(val(eve::nextafter[mask](a0, vda1))  , eve::nextafter[mask](a0, a1));
};
