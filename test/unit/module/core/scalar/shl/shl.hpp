//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SHL_HPP
#define SHL_HPP

#include <eve/function/scalar/shl.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE("Check shl return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  TTS_EXPR_IS(eve::shl(Type(), Type()), Type);
  TTS_EXPR_IS(eve::shl(Type(), i_t()), Type);
  TTS_EXPR_IS(eve::shl(Type(), u_t()), Type);
  TTS_EXPR_IS(eve::shl(i_t(), Type()), i_t);
  TTS_EXPR_IS(eve::shl(u_t(), Type()), u_t);
}

TTS_CASE("Check eve::shl behavior")
{
  TTS_EQUAL(eve::shl(eve::One<Type>(), 4), Type(16));
  TTS_EQUAL(eve::shl(Type(3), 2), Type(12));
  TTS_EQUAL(eve::shl(eve::Allbits<Type>(), 0), eve::Allbits<Type>());
  TTS_EQUAL(eve::shl(eve::Zero<Type>(), 3), eve::Zero<Type>());
}

#endif
