//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_LESS_HPP
#define IS_NOT_LESS_HPP

#include <eve/function/scalar/is_not_less.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check is_not_less return type")
{
  TTS_EXPR_IS(eve::is_not_less(Type(), Type()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_less behavior")
{
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_not_less(Type(1), eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_not_less(eve::Nan<Type>(), Type(1)), eve::True<Type>());
  }
  TTS_EQUAL(eve::is_not_less(Type(1), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(3), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(1), Type(3)), eve::False<Type>());
}

#endif
