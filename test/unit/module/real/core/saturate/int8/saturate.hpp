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
{
  TTS_EXPR_IS(eve::saturate(T(), eve::as<std::int8_t>()), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()), T(eve::valmin(eve::as<std::int8_t>())) );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()), T(0) );
  }

  TTS_EQUAL(eve::saturate(T(0)    , eve::as<std::int8_t>()), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::int8_t>()), T(42.69) );
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::int8_t>()), T(eve::valmax(eve::as<std::int8_t>())) );
}
