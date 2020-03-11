//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::big_(eve::cos) return type")
{
  TTS_EXPR_IS(eve::big_(eve::cos)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::big_(eve::cos) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  auto std_cos = [](auto e) { return std::cos(double(e)); };
  
  TTS_ULP_EQUAL(eve::big_(eve::cos)(EVE_TYPE(1)), EVE_TYPE(std_cos(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(EVE_TYPE(-1)),EVE_TYPE(std_cos(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cos)(EVE_TYPE(0)), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::big_(eve::cos)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std_cos(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std_cos(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(100000.0))), EVE_TYPE(std_cos(100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(-100000.0))),EVE_TYPE(std_cos(-100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(100000000.0))), EVE_TYPE(std_cos(100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(-100000000.0))),EVE_TYPE(std_cos(-100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))),EVE_TYPE(std_cos(eve::Valmax<EVE_VALUE>())), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))/10),EVE_TYPE(std_cos(eve::Valmax<EVE_VALUE>())/10), 0.5);

}
