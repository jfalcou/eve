//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REC_HPP
#define REC_HPP

#include <eve/function/scalar/rec.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/as_logical.hpp>

TTS_CASE("Check rec return type")
{
  TTS_EXPR_IS(eve::rec(Type(0)),  Type);
}

TTS_CASE("Check eve::rec behavior")
{
  if constexpr(std::is_floating_point<Type>)
  {
    TTS_EQUAL(eve::rec(Type{0}), Type(0));
    TTS_EQUAL(eve::rec(Type{1}), Type(1));
    TTS_EQUAL(eve::rec(Type{2}), Type(1)/Type(2));
  }
  else
  {
    TTS_EQUAL(eve::rec(Type{0}), Nan<Type>());
    TTS_EQUAL(eve::rec(Type{1}), Type(1));  
    TTS_EQUAL(eve::rec(Type{2}), Type(0));
  }

}

#endif
