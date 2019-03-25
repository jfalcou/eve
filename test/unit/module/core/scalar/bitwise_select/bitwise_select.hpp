//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SELECT_HPP
#define BITWISE_SELECT_HPP

#include <eve/function/scalar/bitwise_select.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>  
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE( "Check bitwise_select return type" )
{
  using i_t =  eve::detail::as_integer_t<Type, signed>; 
  using u_t =  eve::detail::as_integer_t<Type, unsigned>;   
  TTS_EXPR_IS(eve::bitwise_select(Type(), Type(), Type()) , Type);
  TTS_EXPR_IS(eve::bitwise_select(Type(), i_t (), i_t ()) , i_t);
  TTS_EXPR_IS(eve::bitwise_select(Type(), u_t (), u_t ()) , u_t);
  TTS_EXPR_IS(eve::bitwise_select(i_t(), Type(), Type()) , Type );
  TTS_EXPR_IS(eve::bitwise_select(u_t(), Type(), Type()) , Type );
}

TTS_CASE("Check eve::bitwise_select behavior")
{
  TTS_EQUAL(eve::bitwise_select(eve::Zero<Type>(), eve::One<Type>(),eve::Inf<Type>()), eve::Inf<Type>());
  TTS_EQUAL(eve::bitwise_select(eve::Allbits<Type>(), eve::Zero<Type>(),eve::Inf<Type>()), eve::Zero<Type>());
}

#endif
