//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/next.hpp>
#include <eve/function/all.hpp>
#include <eve/function/next.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/sequence.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <array>
#include <cmath>

TTS_CASE("Check eve::sinhcosh return type")
{
  TTS_EXPR_IS(eve::sinhcosh(Type(0)), (std::tuple<Type, Type>));
}

TTS_CASE("Check eve::sinhcosh behavior")
{
  if constexpr(eve::platform::supports_infinites)
  {
    std::array<Value, 3> a = {eve::Nan<Value>(), eve::Inf<Value>(), eve::Minf<Value>()};
    
    for(int i=0; i < 3 ; ++i)
    {
      auto [sh, ch] = eve::sinhcosh(Type(a[i])); 
      TTS_IEEE_EQUAL(sh, (Type(std::sinh(a[i]))));
      TTS_IEEE_EQUAL(ch, (Type(std::cosh(a[i]))));
    }
  }
  Value ovflimit =  eve::Ieee_constant<Value,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
  std::array<Value, 10> a = {Value(1), Value(-1), Value(0), Value(-0.0), Value(10), Value(-10)
                             , eve::Maxlog<Value>(), ovflimit/2, ovflimit, 2*ovflimit};
  
  for(size_t i=0; i < a.size(); ++i)
  {
    auto [sh, ch] = eve::sinhcosh(Type(a[i]));
    auto  sh1     = std::sinh(a[i]);
    auto  ch1     = std::cosh(a[i]);
    std::cout << " ======================== " << std::endl; 
    TTS_ULP_EQUAL(sh, (Type(sh1)), 0.5);
    TTS_ULP_EQUAL(ch, (Type(ch1)), 0.5);
    std::cout  <<" a[" << i << "] " << std::setprecision(20) << a[i]<< std::endl;
    std::cout  <<" sh   " << std::setprecision(20) << sh << std::endl;
    std::cout  <<" sh1  " << std::setprecision(20) << sh1 << std::endl;
    std::cout  <<" ch   " << std::setprecision(20) << ch << std::endl;
    std::cout  <<" ch1  " << std::setprecision(20) << ch1 << std::endl;
    std::cout << " ************************ " << std::endl; 
  }
  {  
    auto [sh, ch] = eve::sinhcosh(Type(-0.0)); 
    TTS_EXPECT(eve::all(eve::is_negative(sh)));
  }
  {
    auto [sh, ch] = eve::sinhcosh(Type(0.0)); 
    TTS_EXPECT(eve::all(eve::is_positive(sh)));
  }
}



