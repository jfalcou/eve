//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef RSHR_HPP
#define RSHR_HPP

#include <eve/function/scalar/rshr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>


TTS_CASE( "Check rshr return type" )
{
  using i_t =  eve::detail::as_integer_t<Type, signed>;
  using u_t =  eve::detail::as_integer_t<Type, unsigned>;   
  TTS_EXPR_IS(eve::rshr(Type(), Type()) , Type);
  TTS_EXPR_IS(eve::rshr(Type(), i_t ()) , Type);
  TTS_EXPR_IS(eve::rshr(Type(), u_t ()) , Type);
  TTS_EXPR_IS(eve::rshr(i_t(), Type()) , i_t );
  TTS_EXPR_IS(eve::rshr(u_t(), Type()) , u_t );
}

TTS_CASE("Check eve::rshr behavior")
{
  TTS_EQUAL(eve::rshr(Type(64),2), Type(16));
  TTS_EQUAL(eve::rshr(Type(127), 2), Type(31));
  TTS_EQUAL(eve::rshr(eve::Allbits<Type>(), 0), eve::Allbits<Type>());
  TTS_EQUAL(eve::rshr(eve::One<Type>(), -3), Type(8) );
  TTS_EQUAL(eve::rshr(Type(8), -2), Type(32));
}

#endif
