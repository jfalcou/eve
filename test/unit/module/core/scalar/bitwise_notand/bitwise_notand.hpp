//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_NOTAND_HPP
#define BITWISE_NOTAND_HPP

#include <eve/function/scalar/bitwise_notand.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE( "Check bitwise_notand return type" )
{
  using i_t =  eve::detail::as_integer_t<Type, signed>;
  using u_t =  eve::detail::as_integer_t<Type, unsigned>;   
  TTS_EXPR_IS(eve::bitwise_notand(Type(), Type()) , Type);
  TTS_EXPR_IS(eve::bitwise_notand(Type(), i_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_notand(Type(), u_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_notand(i_t(), Type()) , i_t );
  TTS_EXPR_IS(eve::bitwise_notand(u_t(), Type()) , u_t );
}

TTS_CASE("Check eve::bitwise_notand behavior")
{
  TTS_EQUAL(eve::bitwise_notand(eve::Zero<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_notand(eve::One<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::bitwise_notand(eve::Allbits<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_IEEE_EQUAL(eve::bitwise_notand(eve::Zero<Type>(), eve::Allbits<Type>()), eve::Allbits<Type>() );              
}

#endif
