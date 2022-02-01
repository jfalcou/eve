//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_odd.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/dec.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_odd", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  if constexpr(eve::floating_value<T>)
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
};