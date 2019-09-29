//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include <eve/function/scalar/binarize.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/scalar/is_greater.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check binarize return type") {
  TTS_EXPR_IS(eve::binarize(eve::logical<Type>()), Type);
  TTS_EXPR_IS(eve::binarize(eve::logical<Type>(), int()), Type);
}

TTS_CASE("Check eve::binarize on logicals behavior")
{
  TTS_EQUAL(eve::binarize(eve::is_greater(Type{1}, Type(2))), Type(0));
  TTS_EQUAL(eve::binarize(eve::is_greater(Type{2}, Type(1))), Type(1));
  
  if constexpr(std::is_signed_v<Type>) {
    TTS_EQUAL(eve::binarize(eve::is_greater(Type{2},  Type(1)), Type(-2)), Type(-2));
    TTS_EQUAL(eve::binarize(eve::is_greater(Type{0}, Type(1)), Type(-2)), Type(0));
    TTS_EQUAL(eve::binarize(eve::is_greater(Type{1}, Type(2)), eve::mone_), Type(0));
    TTS_EQUAL(eve::binarize(eve::is_greater(Type{2}, Type(1)), eve::mone_), Type(-1));
  }
  TTS_EQUAL(eve::binarize(eve::is_greater(Type{2}, Type(1)), Type(2)), Type(2));
  TTS_EQUAL(eve::binarize(eve::is_greater(Type{0}, Type(1)), Type(2)), Type(0));
  TTS_EQUAL(eve::binarize(eve::is_greater(Type{0}, Type(1)), eve::allbits_), Type(0));
  TTS_IEEE_EQUAL(eve::binarize(eve::is_greater(Type{2}, Type(1)), eve::allbits_), eve::Allbits<Type>());
}


#endif
