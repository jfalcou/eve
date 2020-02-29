//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinh.hpp>
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

TTS_CASE("Check eve::sinh return type")
{
  TTS_EXPR_IS(eve::sinh(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::sinh behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sinh(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::sinh(eve::Minf<Type>()), (eve::Minf<Type>()) );   
  }
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(eve::Mzero<Type>()))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(Type(0))))            );
  
  Value ovflimit =  eve::Ieee_constant<Value,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
  std::array<Value, 10> a = {Value(1), Value(-1), Value(0), Value(-0.0), Value(10), Value(-10)
                             , eve::Maxlog<Value>(), ovflimit/2, ovflimit, 2*ovflimit};
  
  for(size_t i=0; i < a.size(); ++i)
  {
    auto sh  = eve::sinh(Type(a[i]));
    Value sh1 = std::sinh(double(a[i]));
    std::cout << " ======================== " << std::endl; 
    TTS_ULP_EQUAL(sh, (Type(sh1)), 0.5);
    std::cout  <<" a[" << i << "] " << std::setprecision(20) << a[i]<< std::endl;
    std::cout  <<" sh   " << std::setprecision(20) << sh << std::endl;
    std::cout  <<" sh1  " << std::setprecision(20) << sh1 << std::endl;
    std::cout << " ************************ " << std::endl; 
  }
}
