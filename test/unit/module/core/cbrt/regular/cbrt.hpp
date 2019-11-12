//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cbrt return type")
{
  TTS_EXPR_IS(eve::cbrt(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cbrt behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cbrt(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::Minf<Type>()), (eve::Minf<Type>()) );   
  }

  TTS_ULP_EQUAL(eve::cbrt(Type(1)) ,  Type(1) , 0.5);
  TTS_ULP_EQUAL(eve::cbrt(Type(-1)),  Type(-1), 0.5); 
  TTS_ULP_EQUAL(eve::cbrt(Type(8)) ,  Type(2) , 0.5);
  TTS_ULP_EQUAL(eve::cbrt(Type(-8)),  Type(-2), 0.5);                     
  TTS_ULP_EQUAL(eve::cbrt(Type(0)) ,  Type(0) , 0);
  TTS_ULP_EQUAL((eve::cbrt(eve::Mzero<Type>())), Type(0), 0.5);
  
  TTS_EXPECT( all(is_negative(eve::cbrt(eve::Mzero<Type>()))) );
  TTS_EXPECT( all(is_positive(eve::cbrt(Type(0))))            );
}
