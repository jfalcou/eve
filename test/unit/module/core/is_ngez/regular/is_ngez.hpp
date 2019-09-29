//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NGEZ_HPP
#define IS_NGEZ_HPP

#include <eve/function/scalar/is_ngez.hpp>
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

TTS_CASE("Check is_ngez return type")
{
  TTS_EXPR_IS(eve::is_ngez(Type()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_ngez behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_ngez(Type(-1)), eve::True<Type>());
  }
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_ngez(eve::Nan<Type>()), eve::True<Type>());
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_ngez(eve::Mzero<Type>()), eve::False<Type>());
  }
  TTS_EQUAL(eve::is_ngez(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_ngez(Type(3)), eve::False<Type>());
}

#endif
