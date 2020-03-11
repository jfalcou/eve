//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/function/sin.hpp>    
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/next.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::medium_(eve::cos) return type")
{
  TTS_EXPR_IS(eve::medium_(eve::cos)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::medium_(eve::cos) behavior")
{
  auto std_cos = [](auto e) { return std::cos(double(e)); };
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::cos)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cos)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cos)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::cos)(EVE_TYPE(1)), EVE_TYPE(std_cos(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cos)(EVE_TYPE(-1)),EVE_TYPE(std_cos(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::cos)(EVE_TYPE(0)), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL(eve::medium_(eve::cos)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std_cos(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std_cos(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(EVE_TYPE(100.0))), EVE_TYPE(std_cos(EVE_VALUE(100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(EVE_TYPE(-100.0))),EVE_TYPE(std_cos(EVE_VALUE(-100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(EVE_TYPE(100000.0))), EVE_TYPE(std_cos(EVE_VALUE(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cos)(EVE_TYPE(-100000.0))),EVE_TYPE(std_cos(EVE_VALUE(-100000.0))), 0.5);
}

