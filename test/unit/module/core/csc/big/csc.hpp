//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
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
#include <cmath>

TTS_CASE("Check eve::big_(eve::csc) return type")
{
  TTS_EXPR_IS(eve::big_(eve::csc)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::big_(eve::csc) behavior")
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(double(x)));}; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::csc)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::csc)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::csc)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::csc)(EVE_TYPE(1)), EVE_TYPE(my_stdcsc(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::big_(eve::csc)(EVE_TYPE(-1)),EVE_TYPE(my_stdcsc(-1.0)), 1.0); 
  TTS_ULP_EQUAL(eve::big_(eve::csc)(EVE_TYPE(0)), (EVE_TYPE(my_stdcsc(EVE_VALUE(0)))), 0);
  TTS_ULP_EQUAL(eve::big_(eve::csc)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(my_stdcsc(eve::Mzero<EVE_VALUE>()))), 0);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(my_stdcsc(eve::Pio_4<EVE_VALUE>()))), 0.75);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(my_stdcsc(-eve::Pio_4<EVE_VALUE>()))), 0.75);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(100000.0))), EVE_TYPE(my_stdcsc(100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(-100000.0))),EVE_TYPE(my_stdcsc(-100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(100000000.0))), EVE_TYPE(my_stdcsc(100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(-100000000.0))),EVE_TYPE(my_stdcsc(-100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))),EVE_TYPE(my_stdcsc(eve::Valmax<EVE_VALUE>())), 1.5);
  TTS_ULP_EQUAL((eve::big_(eve::csc)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))/10),EVE_TYPE(my_stdcsc(eve::Valmax<EVE_VALUE>())/10), 1.5);     
}
