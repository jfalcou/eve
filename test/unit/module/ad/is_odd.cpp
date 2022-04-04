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

EVE_TEST( "Check behavior of eve::is_odd(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, 10)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, M const & t)
{
  using eve::detail::map;
  auto vda0 = eve::var(a0);

  TTS_EQUAL(eve::is_odd(vda0), eve::is_odd(a0));
  TTS_EQUAL(eve::is_odd[t](vda0), eve::if_else(t, eve::is_odd(a0), eve::false_(eve::as(a0))));
};
