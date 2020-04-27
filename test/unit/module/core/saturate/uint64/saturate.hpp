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
  TTS_EXPR_IS(eve::saturate( (T()), eve::as<std::uint64_t>()), T);
  TTS_EXPR_IS(eve::saturate( (T()), eve::uint64_            ), T);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<T>(), eve::uint64_), (T(0)));
    TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint64_), (T(eve::Valmax<std::uint64_t>())) );
  }
  else
  {
    TTS_EQUAL(eve::saturate((T(0)), eve::uint64_          ), (T(0))     );
    TTS_EQUAL(eve::saturate((T(42.69)), eve::uint64_      ), (T(42.69)) );

    if constexpr(eve::signed_value<T>)
    {
      if constexpr(sizeof(v_t) <= sizeof(std::int64_t))
      {
        TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint64_), eve::Valmax<T>() );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint64_), (T(eve::Valmax<std::uint64_t>())) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmax<T>(), eve::uint64_), (T(eve::Valmax<std::uint64_t>())) );
    }
  }
}
