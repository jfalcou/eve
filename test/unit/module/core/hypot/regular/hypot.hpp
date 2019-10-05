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

#include <eve/function/hypot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check hypot return type")
{
  TTS_EXPR_IS(eve::hypot(Type(0), Type(0)),  Type);
}

TTS_CASE("Check eve::hypot behavior")
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }
  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<Type>(), eve::Valmax<Type>()), eve::Inf<Type>(), 0);
  // up to here
  TTS_ULP_EQUAL(eve::hypot(eve::Mone<Type>(), eve::Mone<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::One<Type>(), eve::One<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2), 0.5);
}

#endif
