//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_OR_HPP
#define BITWISE_OR_HPP

#include <eve/function/bitwise_or.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_or return type")
{
  TTS_EXPR_IS(eve::bitwise_or(Type(), Type()), Type);
  TTS_EXPR_IS(eve::bitwise_or(Type(), eve::detail::as_integer_t<Type>()), Type);
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>;
  TTS_EXPR_IS(eve::bitwise_or(Type(),ui_t()) , Type);
  TTS_EXPR_IS(eve::bitwise_or(Type(),si_t()) , Type);
  TTS_EXPR_IS(eve::bitwise_or(ui_t(), Type()), ui_t);
  TTS_EXPR_IS(eve::bitwise_or(si_t(), Type()), si_t);
}

TTS_CASE( "Check bitwise_or behavior")
{
  TTS_EQUAL(eve::bitwise_or(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::bitwise_or(eve::Zero<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_or(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_or(Type(3), Type(2)), Type(3));
    TTS_EQUAL(eve::bitwise_or(Type(2), Type(1)), Type(3));
    using ui_t = eve::detail::as_integer_t<Type, unsigned>;
    using si_t = eve::detail::as_integer_t<Type, signed>;
    TTS_EQUAL(eve::bitwise_or(eve::One<Type>(), eve::Zero<ui_t>()), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_or(eve::One<Type>(), eve::Zero<si_t>()), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_or(eve::One<ui_t>(), eve::Zero<Type>()), eve::One<ui_t>());
    TTS_EQUAL(eve::bitwise_or(eve::One<si_t>(), eve::Zero<Type>()), eve::One<si_t>());
  }
}

#endif
