//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SHL_HPP
#define BITWISE_SHL_HPP

#include <eve/function/bitwise_shl.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_shl return type")
{
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>;
  TTS_EXPR_IS(eve::bitwise_shl(Type(), int()),  Type);
  TTS_EXPR_IS(eve::bitwise_shl(Type(), ui_t()), Type);
  TTS_EXPR_IS(eve::bitwise_shl(Type(), si_t()), Type);

}

TTS_CASE( "Check bitwise_shl behavior")
{
  TTS_EQUAL(eve::bitwise_shl(Type(7),Type(4)), Type(112));
  TTS_EQUAL(eve::bitwise_shl(eve::One<Type>(),eve::One<Type>()), Type(2));
  TTS_EQUAL(eve::bitwise_shl(eve::One<Type>(),eve::Zero<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_shl(eve::Zero<Type>(),eve::One<Type>()), eve::Zero<Type>());

}

#endif
