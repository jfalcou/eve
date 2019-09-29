//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef UNARY_PLUS_HPP
#define UNARY_PLUS_HPP

#include <eve/function/scalar/unary_plus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>  
#include <type_traits>

TTS_CASE("Check unary_plus return type")
{
  TTS_EXPR_IS(eve::unary_plus(Type()), Type);
}

TTS_CASE("Check  eve::unary_plus behaviour")
{
  TTS_EQUAL(eve::unary_plus(eve::One<Type>()),  eve::One<Type>());
}

#endif
