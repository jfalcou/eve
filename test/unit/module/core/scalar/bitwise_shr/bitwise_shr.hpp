//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SHR_HPP
#define BITWISE_SHR_HPP

#include <eve/function/scalar/bitwise_shr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE( "Check bitwise_shr return type" )
{
  using i_t =  eve::detail::as_integer_t<Type, signed>;
  using u_t =  eve::detail::as_integer_t<Type, unsigned>;   
  TTS_EXPR_IS(eve::bitwise_shr(Type(), Type()) , Type);
  TTS_EXPR_IS(eve::bitwise_shr(Type(), i_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_shr(Type(), u_t ()) , Type);
  TTS_EXPR_IS(eve::bitwise_shr(i_t(), Type()) , i_t );
  TTS_EXPR_IS(eve::bitwise_shr(u_t(), Type()) , u_t );
}

TTS_CASE("Check eve::bitwise_shr behavior")
{
  TTS_EQUAL(eve::bitwise_shr(Type(16), 4), Type(1));
  TTS_EQUAL(eve::bitwise_shr(Type(12), 2), Type(3));
  TTS_EQUAL(eve::bitwise_shr(eve::Allbits<Type>(), 0), eve::Allbits<Type>());
  TTS_EQUAL(eve::bitwise_shr(eve::Zero<Type>(), 3), eve::Zero<Type>() );
}

#endif
