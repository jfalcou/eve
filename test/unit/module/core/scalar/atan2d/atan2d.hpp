//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAN2D_HPP
#define ATAN2D_HPP

#include <eve/function/scalar/atan2d.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <type_traits>

TTS_CASE("Check atan2d return type")
{
  TTS_EXPR_IS(eve::atan2d(Type(0), Type(0)),  Type);
}

TTS_CASE("Check eve::atan2d behavior")
{
  using eve::atan2d;

  using r_t = decltype(atan2d(Type(), Type()));
  // return type conformity test
  TTS_TYPE_IS(r_t, Type);

  // specific values tests
#ifndef EVE_NO_INVALIDS
  TTS_ULP_EQUAL(eve::atan2d(eve::Inf<Type>(),eve::One<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Inf<Type>(),eve::Mone<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(),eve::One<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(),eve::Mone<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(), eve::Minf<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mone<Type>(), eve::Minf<Type>()), -Type(180), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(), eve::Inf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mone<Type>(), eve::Inf<Type>()), -Type(0), 0.5);
  TTS_EXPECT(eve::is_negative(eve::atan2d(eve::Mone<Type>(), eve::Inf<Type>())));
  TTS_EXPECT(eve::is_positive(eve::atan2d(eve::One<Type>(), eve::Inf<Type>())));

  TTS_ULP_EQUAL(eve::atan2d(eve::Inf<Type>(),eve::One<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(),eve::One<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<r_t>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Nan<Type>(), eve::Zero<Type>()), eve::Nan<r_t>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Zero<Type>(), eve::Nan<Type>()), eve::Nan<r_t>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(),eve::Inf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(),eve::Minf<Type>()), Type(180), 0.5);
#endif
  TTS_ULP_EQUAL(eve::atan2d(eve::Half<Type>(), eve::Half<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mhalf<Type>(), eve::Mhalf<Type>()), -r_t(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mone<Type>(), eve::Mone<Type>()), -r_t(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(), eve::One<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mzero<Type>(), eve::Mone<Type>()), -Type(180), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Zero<Type>(), eve::Mone<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mone<Type>(), eve::Mzero<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::Mone<Type>(), eve::Zero<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(), eve::Mzero<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::atan2d(eve::One<Type>(), eve::Zero<Type>()), Type(90), 0.5);
  //result non conform to the standard
 TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(),eve::Minf<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Inf<Type>(),eve::Minf<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(),eve::Inf<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Inf<Type>(),eve::Inf<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Minf<Type>(), eve::Minf<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Zero<Type>(), eve::Zero<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Mzero<Type>(), eve::Mzero<Type>()), eve::Nan<r_t>(), 0.5);
 TTS_ULP_EQUAL(eve::atan2d(eve::Zero<Type>(), eve::Mzero<Type>()), eve::Nan<r_t>(), 0.5);

}

TTS_CASE("Check eve::atan2d pedantic behavior")
{
  using eve::atan2d;
  using eve::pedantic_; 
  using r_t = decltype(pedantic_(atan2d)(Type(), Type()));
  // return type conformity test
  TTS_TYPE_IS(r_t, Type);

  // specific values tests
#ifndef EVE_NO_INVALIDS
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(),eve::One<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(),eve::Mone<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(),eve::One<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(),eve::Mone<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(), eve::Minf<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Minf<Type>()), -Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(), eve::Inf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Inf<Type>()), -Type(0), 0.5);
  TTS_EQUAL(eve::is_negative(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Inf<Type>())), eve::True<Type>());
  TTS_EQUAL(eve::is_positive(eve::pedantic_(atan2d)(eve::One<Type>(), eve::Inf<Type>())), eve::True<Type>());
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(),eve::Minf<Type>()), -Type(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(),eve::Minf<Type>()), Type(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(),eve::Inf<Type>()), -Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(),eve::Inf<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(), eve::Inf<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Inf<Type>(),eve::One<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(), eve::Minf<Type>()), -Type(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Minf<Type>(),eve::One<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Nan<Type>(), eve::Zero<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Zero<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(),eve::Inf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(),eve::Minf<Type>()), Type(180), 0.5);
#endif
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Half<Type>(), eve::Half<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mhalf<Type>(), eve::Mhalf<Type>()), -Type(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Mone<Type>()), -Type(3)*Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(), eve::One<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Zero<Type>(), eve::Zero<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mzero<Type>(), eve::Zero<Type>()), eve::Mzero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mzero<Type>(), eve::Mzero<Type>()), -Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mzero<Type>(), eve::Mone<Type>()), -Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Zero<Type>(), eve::Mzero<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Zero<Type>(), eve::Mone<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Mzero<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::Mone<Type>(), eve::Zero<Type>()), -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(), eve::Mzero<Type>()), Type(90), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(atan2d)(eve::One<Type>(), eve::Zero<Type>()), Type(90), 0.5);

 
}

#endif
