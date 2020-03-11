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
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/all.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::small_(eve::csc) return type")
{
  TTS_EXPR_IS(eve::small_(eve::csc)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::small_(eve::csc) behavior")
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(double(x)));}; 
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::small_(eve::csc)(EVE_TYPE(1)),  EVE_TYPE(my_stdcsc(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(EVE_TYPE(-1)), EVE_TYPE(my_stdcsc(-1.0)), 0.5); 
  TTS_IEEE_EQUAL((eve::small_(eve::csc)(EVE_TYPE(0))), (EVE_TYPE(my_stdcsc(EVE_VALUE(0.0)))));
  TTS_IEEE_EQUAL((eve::small_(eve::csc)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(my_stdcsc(EVE_VALUE(-0.0)))));
  TTS_ULP_EQUAL((eve::small_(eve::csc)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(my_stdcsc(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::csc)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(my_stdcsc(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::csc)(eve::Pio_4<EVE_TYPE>()/2)), (EVE_TYPE(my_stdcsc(eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::csc)(-eve::Pio_4<EVE_TYPE>()/2)),(EVE_TYPE(my_stdcsc(-eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::csc)(-eve::Pio_2<EVE_TYPE>())), (EVE_TYPE(my_stdcsc(-eve::Pio_2<EVE_VALUE>()))), 0.5);
  auto z = eve::Pio_2<EVE_VALUE>(); 
  TTS_ULP_EQUAL((eve::small_(eve::csc)(EVE_TYPE(z))), (EVE_TYPE(my_stdcsc(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::csc)(EVE_TYPE(z))), (EVE_TYPE(my_stdcsc(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::csc)(EVE_TYPE(z))), (EVE_TYPE(my_stdcsc(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::csc)(EVE_TYPE(z))), (EVE_TYPE(my_stdcsc(z))), 0.5);

  
}
