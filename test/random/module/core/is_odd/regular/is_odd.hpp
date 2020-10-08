//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_odd.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/dec.hpp>
#include "producers.hpp"

TTS_CASE("wide random check on is_odd")
{

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    auto std_is_odd = [](auto e) ->eve::logical<EVE_VALUE>
      { auto da = eve::dec(e);
        return (e!= da) && eve::is_even(da);
      };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  else
  {
    auto std_is_odd = [](auto e)  ->eve::logical<EVE_VALUE> { return  (e/2)*2!= e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
}
