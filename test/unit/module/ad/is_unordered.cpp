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

EVE_TEST( "Check behavior of eve::is_unordered(simd)"
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

  TTS_EQUAL(eve::is_unordered(vda0, a1), eve::is_unordered(a0, a1));
  TTS_EQUAL(eve::is_unordered[t](vda0, a1), eve::if_else(t, eve::is_unordered(a0, a1), eve::false_(eve::as(a0))));
  TTS_EQUAL(eve::is_unordered(a0, vda1), eve::is_unordered(a0, a1));
  TTS_EQUAL(eve::is_unordered[t](a0, vda1), eve::if_else(t, eve::is_unordered(a0, a1), eve::false_(eve::as(a0))));
  TTS_EQUAL(eve::is_unordered(vda0, vda1), eve::is_unordered(a0, a1));
  TTS_EQUAL(eve::is_unordered[t](vda0, vda1), eve::if_else(t, eve::is_unordered(a0, a1), eve::false_(eve::as(a0))));
};
