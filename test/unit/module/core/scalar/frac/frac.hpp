//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FRAC_HPP
#define FRAC_HPP

#include <eve/function/scalar/frac.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check frac return type")
{
  TTS_EXPR_IS(eve::frac(Type()),  Type);
}

TTS_CASE("Check eve::frac behavior")
{
  TTS_EQUAL(eve::frac(Type{0}), Type(0));
  TTS_EQUAL(eve::frac(Type{2}), Type(0));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::frac(static_cast<Type>(-2)), Type(0));
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::frac(Type(3)/Type(-2)), Type(-1)/2);
    TTS_EQUAL(eve::frac(Type(3)/Type(2)) , Type(1)/2); 
  }
}


#endif
