//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef HYPOT_HPP
#define HYPOT_HPP

#include <eve/function/scalar/hypot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <type_traits>

TTS_CASE("Check eve::hypot behavior")
{
  using eve::hypot;
  // specific values tests
#ifndef EVE_NO_INVALIDS
  TTS_ULP_EQUAL(hypot(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Minf<Type>(), eve::Minf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Inf<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(hypot(eve::Mone<Type>(), eve::Mone<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(hypot(eve::One<Type>(), eve::One<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(hypot(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Zero<Type>(), eve::Valmax<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(hypot(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2), 0.5);
} // end of test for floating_

#endif
