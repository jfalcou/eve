//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::acoth return type")
{
  TTS_EXPR_IS(eve::acoth(Type(0)), (Type));
}

TTS_CASE("Check eve::acoth behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acoth(eve::Nan<Type>()) , eve::Nan<Type>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acoth( Type( 1.0)), eve::Inf<Type>()  , 0);
    TTS_ULP_EQUAL(eve::acoth( Type(-1.0)), eve::Minf<Type>() , 0);
  }
  
  TTS_ULP_EQUAL(eve::acoth(Type( 2.))         ,  Type(std::atanh(Value(0.5)))  , 0.5  );
  TTS_ULP_EQUAL(eve::acoth(Type(-2.))         ,  Type(std::atanh(Value(-0.5))) , 0.5  );
  TTS_ULP_EQUAL(eve::acoth(Type( 0. ))        ,   eve::Nan<Type>()   , 0  );
}
