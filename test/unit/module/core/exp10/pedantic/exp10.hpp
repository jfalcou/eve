//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
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

TTS_CASE("Check eve::pedantic_(eve::exp10) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::exp10)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::exp10) behavior")
{
  
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp10)(EVE_TYPE(1)), EVE_TYPE(10), 0.5);
  TTS_IEEE_EQUAL((eve::pedantic_(eve::exp10)(EVE_TYPE(0))), (EVE_TYPE(1)));
  if constexpr(std::is_floating_point_v<EVE_TYPE>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp10)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp10)(eve::Inf<EVE_TYPE>()) , (eve::Inf<EVE_TYPE>()) );
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp10)(eve::Minf<EVE_TYPE>()), (eve::Zero<EVE_TYPE>()) ); 
    }
    TTS_ULP_EQUAL(eve::pedantic_(eve::exp10)(EVE_TYPE(-1)),EVE_TYPE(0.1), 0.5); 
    TTS_IEEE_EQUAL((eve::pedantic_(eve::exp10)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(1)));
  }
}
