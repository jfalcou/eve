//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ABS_HPP
#define ABS_HPP

#include <eve/function/scalar/abs.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check abs return type")
{
  TTS_EXPR_IS(eve::abs(Type()),  Type);
}

TTS_CASE("Check eve::abs behavior")
{
  TTS_EQUAL(eve::abs(Type{0}), Type(0));
  TTS_EQUAL(eve::abs(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::abs(static_cast<Type>(-2)), Type(2));
  }
}


#endif
