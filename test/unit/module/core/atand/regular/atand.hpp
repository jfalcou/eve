//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAND_HPP
#define ATAND_HPP

#include <eve/function/atand.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/indeg.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check atand return type")
{
  TTS_EXPR_IS(eve::atand(Type(0)),  Type);
}

TTS_CASE("Check eve::eve::atand behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atand(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atand(eve::Inf<Type>()),   Type(90), 0);
    TTS_ULP_EQUAL(eve::atand(eve::Minf<Type>()), -Type(90), 0);
  }
  TTS_ULP_EQUAL(eve::atand(eve::Half<Type>()),  eve::indeg(Type(4.636476090008061e-01)),  0.5);
  TTS_ULP_EQUAL(eve::atand(eve::Mhalf<Type>()), eve::indeg(Type(-4.636476090008061e-01)), 0.5);
  TTS_ULP_EQUAL(eve::atand(eve::Mone<Type>()),  -Type(45),                                0.5);
  TTS_ULP_EQUAL(eve::atand(eve::One<Type>()),   Type(45),                                 0.5);
  TTS_ULP_EQUAL(eve::atand(eve::Zero<Type>()),   eve::Zero<Type>(),                       0.5);
  TTS_EXPECT(eve::is_negative(eve::atand(eve::Mzero<Type>())));
  TTS_EXPECT(eve::is_positive(eve::atand(eve::Zero<Type>())));
}


#endif
