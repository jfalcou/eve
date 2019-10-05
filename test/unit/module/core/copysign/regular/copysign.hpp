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

#include <eve/function/copysign.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <type_traits>

TTS_CASE("Check copysign return type") { TTS_EXPR_IS(eve::copysign(Type(), Type()), Type); }

TTS_CASE("Check eve::copysign behavior")
{
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Mzero<Type>()), eve::Mone<Type>());
    TTS_EQUAL(copysign(eve::One<Type>(), eve::Zero<Type>()), eve::One<Type>());
  }
  if constexpr(std::is_signed_v<Type>)
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
