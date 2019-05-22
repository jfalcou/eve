//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SIGNNZ_HPP
#define SIGNNZ_HPP

#include "test.hpp"
#include <eve/function/scalar/signnz.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check signnz return type")
{
  TTS_EXPR_IS(eve::signnz(Type()),  Type);
}

TTS_CASE("Check eve::signnz behavior")
{
  TTS_EQUAL(eve::signnz(Type{0}), Type(1));
  TTS_EQUAL(eve::signnz(Type{2}), Type(1));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::signnz(static_cast<Type>(-2)), Type(-1));
  }
}

#endif
