//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/function/inc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE( "wide random check on abs")
{
  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    auto std_abs = [](auto e) { return (e < 0) ? -e : e; };
    TTS_RANGE_CHECK( eve::uniform_prng<EVE_VALUE>(-1,1),  std_abs, eve::abs );
  }
  else if constexpr(eve::signed_value<EVE_TYPE>)
  {
    auto vmin = eve::valmin(eve::as<EVE_VALUE>());
    auto vmax = eve::valmax(eve::as<EVE_VALUE>());

    auto std_abs = [](auto e)
    {
      EVE_VALUE z = (e < 0) ? -e : e;
      return z < 0 ? eve::valmax(eve::as(e)) : z;
    };

    TTS_RANGE_CHECK( eve::uniform_prng<EVE_VALUE>( eve::inc(vmin), vmax ), std_abs, eve::abs );
  }
  else
  {
    auto vmin = eve::valmin(eve::as<EVE_VALUE>());
    auto vmax = eve::valmax(eve::as<EVE_VALUE>());

    auto std_abs = [](auto e) { return e; };
    TTS_RANGE_CHECK( eve::uniform_prng<EVE_VALUE>(vmin,vmax), std_abs, eve::abs );
  }
}
