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
#include <eve/function/convert.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturate return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturate((T()), eve::as<float>()), T);
  TTS_EXPR_IS(eve::saturate((T()), eve::single_    ), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturate((T(42.69)),       eve::single_), (T(42.69)) );
  TTS_EQUAL(eve::saturate((T(0))    ,       eve::single_), (T(0))     );
  if constexpr(std::is_same_v<v_t, double>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::single_), (T(eve::Valmax<float>())));
    TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::single_), (T(eve::Valmin<float>())));
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::single_), (eve::Valmax<T>()));
    TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::single_), (eve::Valmin<T>()));
  }
}
