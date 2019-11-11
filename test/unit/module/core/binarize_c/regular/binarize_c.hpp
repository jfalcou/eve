//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize_c.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/logical.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check binarize_c return type")
{
  using eve::binarize_c;
  TTS_EXPR_IS(binarize_c(eve::logical<Type>()), (Type));
  TTS_EXPR_IS(binarize_c(eve::logical<Type>(), int()), (Type));
}

TTS_CASE("Check eve::binarize_c on logicals behavior")
{
  using eve::binarize_c;
  using eve::is_less;
  TTS_EQUAL(binarize_c(is_less(Type{1} , Type(2))), Type(0));
  TTS_EQUAL(binarize_c(is_less(Type{2} , Type(1))), Type(1));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(binarize_c(is_less(Type{2}, Type(1)), Value(-2)), Type(-2));
    TTS_EQUAL(binarize_c(is_less(Type{0}, Type(1)), Value(-2)), Type(0));
    TTS_EQUAL(binarize_c(is_less(Type{1}, Type(2)), eve::mone_), Type(0));
    TTS_EQUAL(binarize_c(is_less(Type{2}, Type(1)), eve::mone_), Type(-1));
  }

  TTS_EQUAL(binarize_c(is_less(Type{2}, Type(1)), Value(2)), Type(2));
  TTS_EQUAL(binarize_c(is_less(Type{0}, Type(1)), Value(2)), Type(0));
  TTS_EQUAL(binarize_c(is_less(Type{0}, Type(1)), eve::allbits_), Type(0));
  TTS_IEEE_EQUAL(binarize_c(is_less(Type{2}, Type(1)), eve::allbits_), (eve::Allbits<Type>()));
}
