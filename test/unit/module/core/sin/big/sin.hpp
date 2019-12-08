//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
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

TTS_CASE("Check eve::sin return type")
{
  TTS_EXPR_IS(eve::sin(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::sin behavior")
{

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(eve::big_(eve::sin)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
//     TTS_IEEE_EQUAL(eve::big_(eve::sin)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
//     TTS_IEEE_EQUAL(eve::big_(eve::sin)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
//   }
//   TTS_ULP_EQUAL(eve::big_(eve::sin)(Type(1)), Type(std::sin(1.0)), 0.5);
//   TTS_ULP_EQUAL(eve::big_(eve::sin)(Type(-1)),Type(std::sin(-1.0)), 0.5);
//   TTS_IEEE_EQUAL(eve::big_(eve::sin)(Type(0)), (Type(0)));
//   TTS_IEEE_EQUAL(eve::big_(eve::sin)(eve::Mzero<Type>()), (Type(0)));
//   TTS_EXPECT(eve::all(eve::is_negative(eve::big_(eve::sin)(eve::Mzero<Type>()))));
//   TTS_EXPECT(eve::all(eve::is_positive(eve::big_(eve::sin)(eve::Zero<Type>()))));
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(eve::Pio_4<Type>())), (Type(std::sin(eve::Pio_4<Value>()))), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(-eve::Pio_4<Type>())),(Type(std::sin(-eve::Pio_4<Value>()))), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(100000.0))), Type(std::sin(100000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(-100000.0))),Type(std::sin(-100000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(100000000.0))), Type(std::sin(100000000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(-100000000.0))),Type(std::sin(-100000000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(eve::Valmax<Type>()))),Type(std::sin(eve::Valmax<Value>())), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::sin)(Type(eve::Valmax<Type>()))/10),Type(std::sin(eve::Valmax<Value>())/10), 0.5);     
  Value z =   2.356272345726733423e+296; //eve::Valmax<Value>(); 
  while(true)
  {
//    std::cout << std::setprecision(20) << "z " << z << std::endl; 
    TTS_ULP_EQUAL(eve::big_(eve::sin)(Type(z)),Type(std::sin(Value(z))), 0.5);
    auto k = eve::ulpdist(eve::big_(eve::sin)(Type(z)),Type(std::sin(Value(z))));
    if (eve::all(k>  0.5))
    {
      std::cout << std::setprecision(20) << z <<  " -> ulp =  " << k << std::endl;
    }
    z/= 5;
    break; 
    if (eve::all(eve::is_eqz(z))) break; 
  }
}
