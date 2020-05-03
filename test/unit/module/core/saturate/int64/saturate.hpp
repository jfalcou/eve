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

TTS_CASE_TPL("Check eve::saturate return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturate(T(), eve::as<std::int64_t>()), T);
  TTS_EXPR_IS(eve::saturate(T(), eve::int64_            ), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturate(T(0)    , eve::int64_ ), T(0)     );
  TTS_EQUAL(eve::saturate(T(42.69), eve::int64_ ), T(42.69) );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::int64_), T(eve::Valmin<std::int64_t>()) );
    TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::int64_), T(eve::Valmax<std::int64_t>()) );
  }
  else
  {
    if constexpr(eve::signed_value<T>)
    {
      using v_t = eve::element_type_t<T>;
      if constexpr(sizeof(v_t) <= sizeof(std::int64_t))
      {
        TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::int64_), eve::Valmin<T>() );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::int64_), T(eve::Valmin<std::int64_t>()) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::int64_), T(0) );
    }

    using v_t = eve::element_type_t<T>;
    if constexpr(sizeof(v_t) < sizeof(std::int64_t))
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::int64_), eve::Valmax<T>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::int64_), T(eve::Valmax<std::int64_t>()) );
    }
  }
}
