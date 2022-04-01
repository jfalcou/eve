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
#include <cmath>

//==================================================================================================
// Tests for eve::is_denormal
//==================================================================================================

EVE_TEST( "Check behavior of eve::nextafter(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, 10)
                              , eve::test::randoms(-10, 10)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, T const& a1, M const & t)
{
  using eve::detail::map;
  auto vda0 = eve::var(a0);
  auto vda1 = eve::var(a1);

  TTS_EQUAL(eve::nextafter(vda0, a1), eve::nextafter(a0, a1));
  TTS_EQUAL(eve::nextafter[t](vda0, a1), eve::nextafter[t](a0, a1));
  TTS_EQUAL(eve::nextafter(a0, vda1), eve::nextafter(a0, a1));
  TTS_EQUAL(eve::nextafter[t](a0, vda1), eve::nextafter[t](a0, a1));
  TTS_EQUAL(eve::nextafter(vda0, vda1), eve::nextafter(a0, a1));
  TTS_EQUAL(eve::nextafter[t](vda0, vda1), eve::nextafter(a0, a1));
};
