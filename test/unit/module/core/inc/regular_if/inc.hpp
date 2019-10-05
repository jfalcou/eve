//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INC_HPP
#define INC_HPP

#include <eve/function/inc.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check inc return type") { TTS_EXPR_IS(eve::inc(Type(), Type()), Type); }

TTS_CASE("Check eve::inc behavior")
{
  TTS_EQUAL(eve::inc[ Type(1) > Type(0) ](Type(1)), Type(2));
  TTS_EQUAL(eve::inc[ Type(1) > Type(2) ](eve::Zero<Type>()), Type(0));

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::inc[-Type(1) > Type(0) ](eve::Zero<Type>()), Type(0));
    TTS_EQUAL(eve::inc[-Type(1) > -Type(2) ](eve::Zero<Type>()), Type(1));
  }
}

#endif
