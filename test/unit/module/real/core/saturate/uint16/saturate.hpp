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

TTS_CASE_TPL("Check eve::saturate return type", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS(eve::saturate(T(), eve::as<std::uint16_t>()), T);
};

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EQUAL(eve::saturate(T(0)    , eve::as<std::uint16_t>() ), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::uint16_t>() ), T(42.69) );

  if constexpr(eve::signed_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    if constexpr(sizeof(v_t) <= sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), eve::valmax(eve::as<T>()) );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), T(eve::valmax(eve::as<std::uint16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint16_t>()), T(eve::valmax(eve::as<std::uint16_t>())) );
  }
};
