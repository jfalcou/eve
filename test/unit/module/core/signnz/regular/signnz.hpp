//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/signnz.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::signnz return type")
{
  TTS_EXPR_IS(eve::signnz(Type()), (Type));
}

TTS_CASE("Check eve::signnz behavior")
{
  TTS_EQUAL(eve::signnz(Type{0}), Type(1));
  TTS_EQUAL(eve::signnz(Type{2}), Type(1));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::signnz(static_cast<Type>(-2)), (Type(-1)));
  }
}
