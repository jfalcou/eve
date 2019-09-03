//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COPYSIGN_HPP
#define COPYSIGN_HPP

#include "test.hpp"
#include <eve/function/copysign.hpp>
#include <eve/constant/signmask.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>

TTS_CASE("Check copysign return type") { TTS_EXPR_IS(eve::copysign(Type(), Type()), Type); }

TTS_CASE("Check eve::copysign behavior")
{
  using eve::wide;

  if constexpr(std::is_floating_point_v<Type>)
  {
#ifndef EVE_NO_INVALIDS
    TTS_EQUAL(copysign(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(copysign(eve::Minf<Type>(), eve::Minf<Type>()), eve::Minf<Type>());
    TTS_IEEE_EQUAL(copysign(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(copysign(eve::Inf<Type>(), eve::Minf<Type>()), eve::Minf<Type>());
    TTS_EQUAL(copysign(eve::Minf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(copysign(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Nan<Type>()), eve::Mone<Type>());
#endif
    TTS_EQUAL(copysign(eve::Mone<Type>(), eve::Mone<Type>()), eve::Mone<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Mzero<Type>()), eve::Mone<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Zero<Type>()), eve::One<Type>());
    TTS_EQUAL(copysign(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  }
  else if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(copysign(eve::Mone<Type>(), eve::Mone<Type>()), eve::Mone<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
    TTS_EQUAL(copysign(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
    TTS_EQUAL(copysign(eve::Mone<Type>(), eve::One<Type>()), eve::One<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Mone<Type>()), eve::Mone<Type>());
    TTS_EQUAL(copysign(eve::Mone<Type>(), eve::Zero<Type>()), eve::One<Type>());
  }
  else
  {
    TTS_EQUAL(copysign(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
    TTS_EQUAL(copysign(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Zero<Type>()), eve::One<Type>());
  }
}

#endif
