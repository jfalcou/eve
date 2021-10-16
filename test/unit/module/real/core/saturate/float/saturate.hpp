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
  TTS_EXPR_IS(eve::saturate(T(), eve::as<float>()), T);
};

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<float>()), T(42.69) );
  TTS_EQUAL(eve::saturate(T(0)    , eve::as<float>()), T(0)     );

  using v_t = eve::element_type_t<T>;

  if constexpr(std::is_same_v<v_t, double>)
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<float>()), T(eve::valmax(eve::as<float>())) );
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<float>()), T(eve::valmin(eve::as<float>())) );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<float>()), eve::valmax(eve::as<T>()) );
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<float>()), eve::valmin(eve::as<T>()) );
  }
};
