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

EVE_TEST( "Check behavior of eve::is_negative(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, 10)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, M const & t)
{
  using eve::detail::map;
  auto vda0 = eve::var(a0);

  TTS_EQUAL(eve::is_negative(vda0), eve::is_negative(a0));
  TTS_EQUAL(eve::is_negative[t](vda0), eve::if_else(t, eve::is_negative(a0), eve::false_(eve::as(a0))));
};
