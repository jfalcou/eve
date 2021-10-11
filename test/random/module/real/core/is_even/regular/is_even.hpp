//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_even.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/function/trunc.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_even", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_is_even =  [](auto e) ->eve::logical<EVE_VALUE> { return bool(e == trunc(e/2)*2); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_even, eve::is_even);
  }
  else
  {
    auto std_is_even =  [](auto e) ->eve::logical<EVE_VALUE> { return e == (e/2)*2; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_even, eve::is_even);
  }
};