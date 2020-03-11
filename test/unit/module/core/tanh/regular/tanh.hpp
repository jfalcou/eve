//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanh.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::tanh return type")
{
  TTS_EXPR_IS(eve::tanh(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::tanh behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::tanh(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::tanh(eve::Inf<EVE_TYPE>()) , (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::tanh(eve::Minf<EVE_TYPE>()), (EVE_TYPE(-1)) );   
  }
  TTS_ULP_EQUAL(eve::tanh(EVE_TYPE(1)), EVE_TYPE(std::tanh(EVE_VALUE(1))), 0.5);
  TTS_ULP_EQUAL(eve::tanh(EVE_TYPE(-1)),EVE_TYPE(std::tanh(EVE_VALUE(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::tanh(EVE_TYPE(0))), (eve::Zero<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::tanh(eve::Mzero<EVE_TYPE>())), (eve::Zero<EVE_TYPE>()));
  TTS_EXPECT(eve::all(eve::is_negative(eve::tanh(eve::Mzero<EVE_TYPE>()))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::tanh(EVE_TYPE(0))))            );
}
