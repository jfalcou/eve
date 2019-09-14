//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOT_HPP
#define ACOT_HPP

#include <eve/function/scalar/acot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check acot return type")
{
  TTS_EXPR_IS(eve::acot(Type(0)),  Type);
}

TTS_CASE("Check eve::acot behavior")  
{
#ifndef BOOST_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::acot(eve::Inf<Type>()), 0, 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::Minf<Type>()), 0, 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::Nan<Type>()), eve::Nan<Type>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::acot(eve::Half<Type>()), Type(1.107148717794090e+00), 1);
  TTS_ULP_EQUAL(eve::acot(eve::Mhalf<Type>()), Type(-1.107148717794090e+00), 1);
  TTS_ULP_EQUAL(eve::acot(eve::Mone<Type>()), Type(-7.853981633974483e-01), 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::One<Type>()), Type(7.853981633974483e-01), 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::Zero<Type>()), Type(1.570796326794897e+00), 1);
  TTS_ULP_EQUAL(eve::acot(eve::rec(eve::Smallestposval<Type>())), eve::Smallestposval<Type>(), 0.5);
}
  
#endif
