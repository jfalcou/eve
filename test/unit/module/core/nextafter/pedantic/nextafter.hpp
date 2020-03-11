//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nextafter.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check nextafter return type")
{
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(EVE_TYPE(), EVE_VALUE())), (EVE_TYPE));
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(EVE_VALUE(), EVE_TYPE())), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::nextafter) one parameter behavior")
{
  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{1}, EVE_TYPE{1})), EVE_TYPE(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{1}, EVE_TYPE{5})), EVE_TYPE(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{2}, EVE_TYPE(0))), EVE_TYPE(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE{1}, EVE_TYPE{1})), EVE_TYPE(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE{1}, EVE_TYPE{5})), EVE_TYPE(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE{2}, EVE_TYPE(0))), EVE_TYPE(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{1}, EVE_VALUE{1})), EVE_TYPE(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{1}, EVE_VALUE{5})), EVE_TYPE(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE{2}, EVE_VALUE(0))), EVE_TYPE(1));

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(-1), EVE_TYPE(-1))), EVE_TYPE(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(-1), EVE_TYPE(5))), EVE_TYPE(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE(-2), EVE_TYPE(-4))), EVE_TYPE(-3));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE(-1), EVE_TYPE(-1))), EVE_TYPE(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE(-1), EVE_TYPE(5))), EVE_TYPE(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE(-2), EVE_TYPE(-4))), EVE_TYPE(-3));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(-1), EVE_VALUE(-1))), EVE_TYPE(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(-1), EVE_VALUE(5))), EVE_TYPE(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(-2), EVE_VALUE(-4))), EVE_TYPE(-3));
    }
    
  }
  else
  {
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<EVE_TYPE>(), EVE_TYPE(2)))        , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_TYPE>(), EVE_TYPE(-1)))        , (eve::One<EVE_TYPE>()-eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_TYPE>(), EVE_TYPE(1)))        , (eve::One<EVE_TYPE>()));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<EVE_VALUE>(), EVE_TYPE(2)))       , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_VALUE>(), EVE_TYPE(-1)))       , (eve::One<EVE_TYPE>()-eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_VALUE>(), EVE_TYPE(1)))       , (eve::One<EVE_TYPE>()));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<EVE_TYPE>(), EVE_VALUE(2)))       , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_TYPE>(), EVE_VALUE(-1)))       , (eve::One<EVE_TYPE>()-eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<EVE_VALUE>(), EVE_TYPE(1)))       , (eve::One<EVE_TYPE>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<EVE_TYPE>(), EVE_TYPE(1)))         , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(1), eve::Nan<EVE_TYPE>()))         , (eve::Nan<EVE_TYPE>()));    
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<EVE_VALUE>(), EVE_TYPE(1)))         , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(EVE_VALUE(1), eve::Nan<EVE_TYPE>()))         , (eve::Nan<EVE_TYPE>()));    
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<EVE_TYPE>(), EVE_VALUE(1)))         , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(EVE_TYPE(1), eve::Nan<EVE_VALUE>()))         , (eve::Nan<EVE_TYPE>()));    
  }
}
