//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_NOTOR_HPP
#define BITWISE_NOTOR_HPP

#include <eve/function/scalar/bitwise_notor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_notor return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  TTS_EXPR_IS(eve::bitwise_notor(Type(), Type()), Type);
  TTS_EXPR_IS(eve::bitwise_notor(Type(), i_t()), Type);
  TTS_EXPR_IS(eve::bitwise_notor(Type(), u_t()), Type);
  TTS_EXPR_IS(eve::bitwise_notor(i_t(), Type()), i_t);
  TTS_EXPR_IS(eve::bitwise_notor(u_t(), Type()), u_t);
}

TTS_CASE("Check eve::bitwise_notor behavior")
{
  TTS_IEEE_EQUAL(eve::bitwise_notor(eve::Zero<Type>(), eve::One<Type>()), eve::Allbits<Type>());
  TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_IEEE_EQUAL(eve::bitwise_notor(eve::Zero<Type>(), eve::Allbits<Type>()), eve::Allbits<Type>());
}

#endif
