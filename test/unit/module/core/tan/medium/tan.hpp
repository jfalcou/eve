//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::medium_(eve::tan) return type")
{
  TTS_EXPR_IS(eve::medium_(eve::tan)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::medium_(eve::tan) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::tan)(EVE_TYPE(1)), EVE_TYPE(std::tan(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::tan)(EVE_TYPE(-1)),EVE_TYPE(std::tan(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::medium_(eve::tan)(EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL((eve::medium_(eve::tan)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::tan)(eve::Mzero<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::tan)(eve::Zero<EVE_TYPE>()))));
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std::tan(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std::tan(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(EVE_TYPE(100.0))), EVE_TYPE(std::tan(EVE_VALUE(100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(EVE_TYPE(-100.0))),EVE_TYPE(std::tan(EVE_VALUE(-100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(EVE_TYPE(100000.0))), EVE_TYPE(std::tan(EVE_VALUE(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(EVE_TYPE(-100000.0))),EVE_TYPE(std::tan(EVE_VALUE(-100000.0))), 0.5);
}

