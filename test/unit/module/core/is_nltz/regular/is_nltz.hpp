//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NLTZ_HPP
#define IS_NLTZ_HPP

#include <eve/function/scalar/is_nltz.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check is_nltz return type")
{
  TTS_EXPR_IS(eve::is_nltz(Type()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_nltz behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_nltz(Type(-1)), eve::False<Type>());
  }
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_nltz(eve::Nan<Type>()), eve::True<Type>());
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_nltz(eve::Mzero<Type>()), eve::True<Type>());
  }
  TTS_EQUAL(eve::is_nltz(Type(0)), eve::True<Type>());
  TTS_EQUAL(eve::is_nltz(Type(3)), eve::True<Type>());
}

#endif
