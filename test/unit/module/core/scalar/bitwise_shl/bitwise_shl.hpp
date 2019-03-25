//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SHL_HPP
#define BITWISE_SHL_HPP

#include <eve/function/scalar/bitwise_shl.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE( "Check bitwise_shl return type" )
{
  using i_t =  eve::detail::as_integer_t<Type, signed>;
  using u_t =  eve::detail::as_integer_t<Type, unsigned>;   
  TTS_EXPR_IS(eve::bitwise_shl(Type(), Type()) , Type);
  TTS_EXPR_IS(eve::bitwise_shl(Type(), i_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_shl(Type(), u_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_shl(i_t(), Type()) , i_t );
  TTS_EXPR_IS(eve::bitwise_shl(u_t(), Type()) , u_t );
}

TTS_CASE("Check eve::bitwise_shl behavior")
{
  TTS_EQUAL(eve::bitwise_shl(eve::One<Type>(), 4), Type(16));
  TTS_EQUAL(eve::bitwise_shl(Type(3), 2), Type(12));
  TTS_EQUAL(eve::bitwise_shl(eve::Allbits<Type>(), 0), eve::Allbits<Type>());
  TTS_EQUAL(eve::bitwise_shl(eve::Zero<Type>(), 3), eve::Zero<Type>() );
}

#endif
