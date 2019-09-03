//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ZERO_ELSE_ONE_HPP
#define IF_ZERO_ELSE_ONE_HPP

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
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](Type(), eve::zero_, eve::one_), Type);
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](eve::logical<Type>(), eve::zero_, eve::one_), Type);
  TTS_EXPR_IS(eve::if_else[ eve::as(Type()) ](true, eve::zero_, eve::one_), Type);
  TTS_EXPR_IS(eve::if_else(Type(), eve::zero_, eve::one_), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), eve::zero_, eve::one_), Type);
}

TTS_CASE("Check if_else(., zero_, one_) behavior ")
{
  auto f = eve::Zero<Type>();
  auto t = eve::One<Type>();

  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](1, eve::zero_, eve::one_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](1.0, eve::zero_, eve::one_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](true, eve::zero_, eve::one_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](eve::True<Type>(), eve::zero_, eve::one_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](t, eve::zero_, eve::one_), f);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](0, eve::zero_, eve::one_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](0.0, eve::zero_, eve::one_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](false, eve::zero_, eve::one_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](eve::False<Type>(), eve::zero_, eve::one_), t);
  TTS_EQUAL(eve::if_else[ eve::as(Type()) ](f, eve::zero_, eve::one_), t);
}

#endif
