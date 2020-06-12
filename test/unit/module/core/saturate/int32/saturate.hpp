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
  TTS_EXPR_IS(eve::saturate(T(),   eve::as<std::int32_t>()), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturate(T(0)    , eve::as<std::int32_t>() ), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::int32_t>() ), T(42.69) );

  if constexpr(eve::floating_value<T>)
  {
     TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::as<std::int32_t>()), T(eve::Valmin<std::int32_t>()) );
     TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::as<std::int32_t>()), T(eve::Valmax<std::int32_t>()) );
  }
  else
  {
    if constexpr(eve::signed_value<T>)
    {
      using v_t = eve::element_type_t<T>;
      if constexpr(sizeof(v_t) <= sizeof(std::int32_t))
      {
        TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::as<std::int32_t>()), eve::Valmin<T>() );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::as<std::int32_t>()), T(eve::Valmin<std::int32_t>()) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::as<std::int32_t>()), T(0) );
    }

    using v_t = eve::element_type_t<T>;
    if constexpr(sizeof(v_t) < sizeof(std::int32_t))
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::as<std::int32_t>()), eve::Valmax<T>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::as<std::int32_t>()), T(eve::Valmax<std::int32_t>()) );
    }
  }
}
