//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/coth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::coth return type")
{
  TTS_EXPR_IS(eve::coth(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::coth behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::coth(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::coth(eve::Inf<EVE_TYPE>()) , (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::coth(eve::Minf<EVE_TYPE>()), (EVE_TYPE(-1)) );   
  }
  TTS_ULP_EQUAL(eve::coth(EVE_TYPE(1)), EVE_TYPE(eve::rec(std::tanh(EVE_VALUE(1)))), 0.5);
  TTS_ULP_EQUAL(eve::coth(EVE_TYPE(-1)),EVE_TYPE(eve::rec(std::tanh(EVE_VALUE(-1)))), 0.5); 
  TTS_IEEE_EQUAL((eve::coth(EVE_TYPE(0))), (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::coth(eve::Mzero<EVE_TYPE>())), (eve::Minf<EVE_TYPE>()));
}
