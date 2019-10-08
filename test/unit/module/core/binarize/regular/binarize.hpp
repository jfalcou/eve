//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/logical.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check binarize return type")
{
  using eve::binarize;
  TTS_EXPR_IS(binarize(eve::logical<Type>()), (Type));
  TTS_EXPR_IS(binarize(eve::logical<Type>(), int()), (Type));
}

TTS_CASE("Check eve::binarize on logicals behavior")
{
  using eve::binarize;
  using eve::is_greater;
  TTS_EQUAL(binarize(is_greater(Type{1} , Type(2))), Type(0));
  TTS_EQUAL(binarize(is_greater(Type{2} , Type(1))), Type(1));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(binarize(is_greater(Type{2}, Type(1)), Value(-2)), Type(-2));
    TTS_EQUAL(binarize(is_greater(Type{0}, Type(1)), Value(-2)), Type(0));
    TTS_EQUAL(binarize(is_greater(Type{1}, Type(2)), eve::mone_), Type(0));
    TTS_EQUAL(binarize(is_greater(Type{2}, Type(1)), eve::mone_), Type(-1));
  }

  TTS_EQUAL(binarize(is_greater(Type{2}, Type(1)), Value(2)), Type(2));
  TTS_EQUAL(binarize(is_greater(Type{0}, Type(1)), Value(2)), Type(0));
  TTS_EQUAL(binarize(is_greater(Type{0}, Type(1)), eve::allbits_), Type(0));
  TTS_IEEE_EQUAL(binarize(is_greater(Type{2}, Type(1)), eve::allbits_), (eve::Allbits<Type>()));
}
