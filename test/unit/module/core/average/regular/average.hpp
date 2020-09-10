//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check average return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::average(T(), T()), T );
}

TTS_CASE_TPL("Check  eve::average behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::average(eve::one(eve::as<T>()) ,  eve::one(eve::as<T>())     ) , eve::one(eve::as<T>())    );
  TTS_EQUAL(eve::average(T( 0 )  , T( 0 )   ) , T( 0 )   );
  TTS_EQUAL(eve::average(eve::One <T>()  , T(3)             ) , T(2)             );
  TTS_EQUAL(eve::average(eve::Valmax<T>(), eve::Valmax<T>() ) , eve::Valmax<T>() );
  TTS_EQUAL(eve::average(eve::Valmin<T>(), eve::Valmin<T>() ) , eve::Valmin<T>() );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::average(eve::mone(eve::as<T>()), eve::mone(eve::as<T>())), eve::mone(eve::as<T>()));
  }
}
