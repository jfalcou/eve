//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturate return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturate((T()), eve::as<std::uint16_t>()), T);
  TTS_EXPR_IS(eve::saturate((T()), eve::uint16_            ), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturate((T(0)), eve::uint16_          ), (T(0))     );
  TTS_EQUAL(eve::saturate((T(42.69)), eve::uint16_       ), (T(42.69)) );

  if constexpr(eve::signed_value<T>)
  {
    if constexpr(sizeof(v_t) <= sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint16_), eve::Valmax<T>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint16_), (T(eve::Valmax<std::uint16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint16_), (T(eve::Valmax<std::uint16_t>())) );
  }
}
