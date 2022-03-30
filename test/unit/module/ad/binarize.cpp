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
// Tests for eve::binarize
//==================================================================================================
EVE_TEST( "Check behavior of eve::binarize(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::binarize(is_lez(vda0), a1))      , eve::binarize(s_lez(a0), a1));
  TTS_EQUAL(der(eve::binarize(is_lez(vda0), a1))      , diff(eve::binarize)(s_lez(a0), a1));
};
