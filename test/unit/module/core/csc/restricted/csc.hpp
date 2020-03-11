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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::csc) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::csc)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::restricted_(eve::csc) behavior")
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(double(x)));}; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::csc)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::csc)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::csc)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::csc)(EVE_TYPE(1)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::csc)(EVE_TYPE(-1)),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL(eve::restricted_(eve::csc)(EVE_TYPE(0)), (EVE_TYPE(my_stdcsc(EVE_VALUE(0.0)))));
  TTS_IEEE_EQUAL(eve::restricted_(eve::csc)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(my_stdcsc(EVE_VALUE(-0.0)))));
  TTS_ULP_EQUAL((eve::restricted_(eve::csc)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(my_stdcsc(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::csc)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(my_stdcsc(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  
  TTS_ULP_EQUAL((eve::restricted_(eve::csc)(eve::Pio_4<EVE_TYPE>()/2)), (EVE_TYPE(my_stdcsc(eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::csc)(-eve::Pio_4<EVE_TYPE>()/2)),(EVE_TYPE(my_stdcsc(-eve::Pio_4<EVE_VALUE>()/2))), 0.5);
}
