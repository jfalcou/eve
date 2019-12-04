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

TTS_CASE("Check eve::tan return type")
{
  TTS_EXPR_IS(eve::tan(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::tan behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tan)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::tan)(Type(1)), Type(std::tan(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::tan)(Type(-1)),Type(std::tan(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::medium_(eve::tan)(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::medium_(eve::tan)(eve::Mzero<Type>())), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::tan)(eve::Mzero<Type>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::tan)(eve::Zero<Type>()))));
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(eve::Pio_4<Type>())), (Type(std::tan(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(-eve::Pio_4<Type>())),(Type(std::tan(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(Type(100.0))), Type(std::tan(Value(100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(Type(-100.0))),Type(std::tan(Value(-100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(Type(100000.0))), Type(std::tan(Value(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tan)(Type(-100000.0))),Type(std::tan(Value(-100000.0))), 0.5);
  auto z =  eve::Ieee_constant < Value, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.76859e+15 (float) et  281474976710656.0 (double)
  while(true)
  {
    std::cout << std::setprecision(20) << "z " << z << std::endl; 
    TTS_ULP_EQUAL(eve::big_(eve::tan)(Type(z)),Type(std::tan(Value(z))), 0.5);
    z/= 5.123;
    if (eve::all(eve::is_eqz(z))) break;
  }
}

