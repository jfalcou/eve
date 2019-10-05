//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_IMAG_HPP
#define IS_NOT_IMAG_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_not_imag.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_not_imag return type")
{
  TTS_EXPR_IS(eve::is_not_imag(Type(0)), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_imag behavior")
{
  TTS_EQUAL(eve::is_not_imag(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_not_imag(Type{2}), eve::True<Type>());
}

#endif
