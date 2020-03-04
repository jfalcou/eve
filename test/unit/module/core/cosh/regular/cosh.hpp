//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cosh return type")
{
  TTS_EXPR_IS(eve::cosh(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cosh behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Minf<Type>()), (eve::Inf<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::cosh(Type(1)), Type(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(Type(-1)),Type(std::cosh(-1.0)), 0.5);
  Value ovflimit =  eve::Ieee_constant<Value,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
  std::array<Value, 10> a = {Value(1), Value(-1), Value(0), Value(-0.0), Value(10), Value(-10)
                             , eve::Maxlog<Value>(), ovflimit/2, ovflimit, 2*ovflimit};
  
  for(size_t i=0; i < a.size(); ++i)
  {
    auto ch  = eve::cosh(Type(a[i]));
    Value ch1 = std::cosh(double(a[i]));
    TTS_ULP_EQUAL(ch, (Type(ch1)), 0.5);
  }
}
