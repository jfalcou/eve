//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_negative.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_negative", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  if constexpr(eve::floating_value<EVE_VALUE>)
  {
    auto std_is_negative =  [](auto e) ->eve::logical<EVE_VALUE> { return std::signbit(e) == 1; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_negative, eve::is_negative);
  }
  else
  {
    auto std_is_negative =  [](auto e) ->eve::logical<EVE_VALUE> { return e < 0; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_negative, eve::is_negative);
  }
};