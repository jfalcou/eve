//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturate return type", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS(eve::saturate(T(),   eve::as<double>()), T);
};

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<double>()), eve::valmin(eve::as<T>()) );
  TTS_EQUAL(eve::saturate(T(0)            , eve::as<double>()), T(0)             );
  TTS_EQUAL(eve::saturate(T(42.69)        , eve::as<double>()), T(42.69)         );
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<double>()), eve::valmax(eve::as<T>()) );
};
