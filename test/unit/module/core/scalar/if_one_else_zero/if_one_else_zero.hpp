//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ONE_ELSE_ZERO_HPP
#define IF_ONE_ELSE_ZERO_HPP

#include <eve/function/scalar/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check if_else(.,  zero_, one_) return type")
{
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](Type(), eve::one_, eve::zero_), Type);
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](eve::logical<Type>(), eve::one_, eve::zero_), Type);
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](true, eve::zero_, eve::one_), Type);
  TTS_EXPR_IS(eve::if_else(Type(), eve::one_, eve::zero_), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), eve::one_, eve::zero_), Type);
}

TTS_CASE("Check if_else(., zero_, one_) behavior ")
{
  auto f = eve::Zero<Type>();
  auto t = eve::One<Type>();

  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](1, eve::one_, eve::zero_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](1.0, eve::one_, eve::zero_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](true, eve::one_, eve::zero_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](eve::True<Type>(), eve::one_, eve::zero_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](t, eve::one_, eve::zero_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](0, eve::one_, eve::zero_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](0.0, eve::one_, eve::zero_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](false, eve::one_, eve::zero_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](eve::False<Type>(), eve::one_, eve::zero_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](f, eve::one_, eve::zero_), f);
}

#endif
