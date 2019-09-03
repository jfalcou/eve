//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQZ_HPP
#define IS_EQZ_HPP

#include <eve/function/scalar/is_eqz.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/as_logical.hpp>

TTS_CASE("Check is_eqz return type") { TTS_EXPR_IS(eve::is_eqz(Type(0)), eve::as_logical_t<Type>); }

TTS_CASE("Check eve::is_eqz behavior")
{
  TTS_EQUAL(eve::is_eqz(Type{0}), eve::True<Type>());
  TTS_EQUAL(eve::is_eqz(Type{2}), eve::False<Type>());
}

#endif
