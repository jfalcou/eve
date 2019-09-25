//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DEGINRAD_HPP
#define DEGINRAD_HPP

#include <eve/function/scalar/deginrad.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/fma.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>
#include <eve/constant/ieee_constant.hpp>

TTS_CASE("Check deginrad return type")
{
  TTS_EXPR_IS(eve::deginrad(Type(0)),  Type);
}

TTS_CASE("Check eve::deginrad behavior")
{
#ifndef BOOST_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::deginrad(eve::Inf<Type>()), eve::Inf<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::Minf<Type>()), eve::Minf<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::Nan<Type>()), eve::Nan<Type>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::deginrad(eve::Zero<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::One<Type>()), Type(0.017453292519943295769236907684886), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(Type(10)),         Type(0.17453292519943295769236907684886), 0.5);   
}

  
#endif
