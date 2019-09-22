//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COS_HPP
#define COS_HPP

#include <eve/function/scalar/cos.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/sqrt_2o_2.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check cos return type")
{
  TTS_EXPR_IS(eve::big_(eve::cos)(Type(0)),  Type);
}

TTS_CASE("Check eve::big_(eve::cos) behavior")
{

#ifndef EVE_NO_INVALIDS 
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Inf<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Minf<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Nan<Type>()), eve::Nan<Type>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::big_(eve::cos)(2*eve::Pi<Type>()), eve::One<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(-2*eve::Pi<Type>()), eve::One<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(-eve::Pio_2<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(-eve::Pio_4<Type>()), eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Pi<Type>()), eve::Mone<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(-eve::Pi<Type>()), eve::Mone<Type>(), 0.5);   
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Pio_2<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Pio_4<Type>()), eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(eve::Zero<Type>()), eve::One<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(3*eve::Pio_4<Type>()/2), Type(0.3826834323650897717284599840304), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(Type(3.836536000e+07)), Type(-0.38268298167737746507), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(Type(262144)), Type(-0.996456726543131), 0.5);
  if constexpr(std::is_same_v<Type, double>)
  {
    TTS_ULP_EQUAL(eve::big_(eve::cos)(3*eve::Pio_2<Type>()), Type(-1.836970198721030e-16),  0.5);
    TTS_ULP_EQUAL(eve::big_(eve::cos)(-3*eve::Pio_2<Type>()),Type(-1.836970198721030e-16),  0.5);      
    TTS_ULP_EQUAL(eve::big_(eve::cos)(31*eve::Pio_2<Type>()), Type(-3.674559378078648e-15),  0.5);
  }
  else
  {
    TTS_ULP_EQUAL(eve::big_(eve::cos)(3*eve::Pio_2<Type>()), Type(1.1924881e-08),  0.5);
    TTS_ULP_EQUAL(eve::big_(eve::cos)(-3*eve::Pio_2<Type>()),Type(1.1924881e-08),  0.5);      
    TTS_ULP_EQUAL(eve::big_(eve::cos)(31*eve::Pio_2<Type>()), Type(7.5900664e-07),  0.5);
    TTS_ULP_EQUAL(eve::big_(eve::cos)(-31*eve::Pio_2<Type>()),Type(7.5900664e-07),  0.5);
  }
}


#endif

