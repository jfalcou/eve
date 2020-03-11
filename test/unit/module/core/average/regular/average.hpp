//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("Check average return type")
{
  TTS_EXPR_IS(eve::average(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE) );
}

TTS_CASE("Check  eve::average behavior")
{
  TTS_EQUAL(eve::average(eve::One<EVE_TYPE>() ,  eve::One<EVE_TYPE>()     ) , eve::One<EVE_TYPE>()    );
  TTS_EQUAL(eve::average(eve::Zero<EVE_TYPE>()  , eve::Zero<EVE_TYPE>()   ) , eve::Zero<EVE_TYPE>()   );
  TTS_EQUAL(eve::average(eve::One <EVE_TYPE>()  , EVE_TYPE(3)             ) , EVE_TYPE(2)             );
  TTS_EQUAL(eve::average(eve::Valmax<EVE_TYPE>(), eve::Valmax<EVE_TYPE>() ) , eve::Valmax<EVE_TYPE>() );
  TTS_EQUAL(eve::average(eve::Valmin<EVE_TYPE>(), eve::Valmin<EVE_TYPE>() ) , eve::Valmin<EVE_TYPE>() );

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::average(eve::Mone<EVE_TYPE>(), eve::Mone<EVE_TYPE>()), eve::Mone<EVE_TYPE>());
  }
}
