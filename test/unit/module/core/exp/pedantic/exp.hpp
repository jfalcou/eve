//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>

TTS_CASE("Check eve::pedantic_(eve::exp) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::exp)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::exp) behavior")
{
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Inf<EVE_TYPE>()) , (eve::Inf<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Minf<EVE_TYPE>()), (eve::Zero<EVE_TYPE>()) ); 
  }
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(EVE_TYPE(1)), EVE_TYPE(std::exp(EVE_VALUE(1))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(EVE_TYPE(-1)),EVE_TYPE(std::exp(EVE_VALUE(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::pedantic_(eve::exp)(EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL((eve::pedantic_(eve::exp)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(1)));
  }
