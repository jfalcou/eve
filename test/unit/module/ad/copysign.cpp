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
EVE_TEST( "Check behavior of eve::copysign(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const& )
{
  using eve::detail::map;
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  auto z = eve::copysign(vda0, a1);
  std::cout << z << std::endl;
//  TTS_EQUAL(val(eve::copysign(vda0, a1))      , eve::copysign(a0, a1));
//   TTS_EQUAL(val(eve::copysign[mask](vda0, a1)), eve::copysign[mask](a0, a1));
//   TTS_EQUAL(der(eve::copysign(vda0, a1))      , diff(eve::copysign)(a0, a1));
//   TTS_EQUAL(der(eve::copysign[mask](vda0, a1)), diff(eve::copysign[mask])(a0, a1));
};
