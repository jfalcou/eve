//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NGEZ_HPP
#define IS_NGEZ_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/as_logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check is_ngez return type")
{
  TTS_EXPR_IS(eve::is_ngez(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_ngez behavior")
{
  TTS_EQUAL(eve::is_ngez(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_ngez(Type{2}), eve::False<Type>());

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_ngez(static_cast<Type>(-2)), eve::True<Type>());
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_ngez(eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_ngez(eve::Mzero<Type>()), eve::False<Type>());
  }

  TTS_EQUAL(eve::is_ngez(eve::True<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::is_ngez(eve::False<Type>()), eve::False<Type>());
}

#endif
