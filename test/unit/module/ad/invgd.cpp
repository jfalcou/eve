//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>

auto maxi = []<typename T>(eve::as<T> const & tgt)
{
  return eve::pio_2(tgt);
};
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return -eve::pio_2(tgt);
};
//==================================================================================================
// Tests for eve::invgd
//==================================================================================================
EVE_TEST( "Check behavior of eve::invgd(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(mini, maxi)
                              )
        )
<typename T>(T const& a0)
{
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::invgd(vda0))      , eve::invgd(a0));
  TTS_EQUAL(der(eve::invgd(vda0))      , diff(eve::invgd)(a0));
};
