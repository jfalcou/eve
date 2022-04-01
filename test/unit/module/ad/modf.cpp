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
// Tests for eve::frac
//==================================================================================================
EVE_TEST( "Check behavior of eve::frac(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  auto [f, t] = eve::modf(vda0);

  TTS_EQUAL(val(f)      , eve::frac(a0));
  TTS_EQUAL(val(t)      , eve::trunc(a0));
  TTS_EQUAL(der(f)      , diff(eve::frac)(a0));
  TTS_EQUAL(der(t)      , diff(eve::trunc)(a0));
};
