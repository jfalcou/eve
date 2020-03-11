//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/constant/pio_2.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::small_(eve::tan) return type")
{
  TTS_EXPR_IS(eve::small_(eve::tan)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::small_(eve::tan) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::small_(eve::tan)(EVE_TYPE(1)),  EVE_TYPE(std::tan(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::tan)(EVE_TYPE(-1)), EVE_TYPE(std::tan(-1.0)), 0.5); 
  TTS_IEEE_EQUAL((eve::small_(eve::tan)(EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL((eve::small_(eve::tan)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::small_(eve::tan)(eve::Mzero<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small_(eve::tan)(eve::Zero<EVE_TYPE>()))));
  TTS_ULP_EQUAL((eve::small_(eve::tan)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std::tan(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::tan)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std::tan(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::tan)(eve::Pio_4<EVE_TYPE>()/2)), (EVE_TYPE(std::tan(eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::tan)(-eve::Pio_4<EVE_TYPE>()/2)),(EVE_TYPE(std::tan(-eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  auto z = eve::Pio_2<EVE_VALUE>(); 
  TTS_ULP_EQUAL((eve::small_(eve::tan)(eve::Pio_2<EVE_TYPE>())), (EVE_TYPE(std::tan(eve::Pio_2<EVE_VALUE>()))), 5.5);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::tan)(EVE_TYPE(z))), (EVE_TYPE(std::tan(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::tan)(EVE_TYPE(z))), (EVE_TYPE(std::tan(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::tan)(EVE_TYPE(z))), (EVE_TYPE(std::tan(z))), 0.5);
}
