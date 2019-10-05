//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_LTZ_HPP
#define IS_LTZ_HPP

#include <eve/function/is_ltz.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check is_ltz return type")
{
  TTS_EXPR_IS(eve::is_ltz(Type()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_ltz behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_ltz(Type(-1)), eve::True<Type>());
  }
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_ltz(eve::Nan<Type>()), eve::False<Type>());
  }
  TTS_EQUAL(eve::is_ltz(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_ltz(Type(3)), eve::False<Type>());
}

#endif
