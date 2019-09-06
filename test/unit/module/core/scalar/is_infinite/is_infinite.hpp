//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_INFINITE_HPP
#define IS_INFINITE_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_infinite return type") { TTS_EXPR_IS(eve::is_infinite(Type(0)), eve::as_logical_t<Type>); }

TTS_CASE("Check eve::is_infinite behavior")
{
  TTS_EQUAL(eve::is_infinite(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_infinite(Type{2}), eve::False<Type>());

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_infinite(eve::Inf<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_infinite(eve::Minf<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_infinite(eve::Nan<Type>()), eve::False<Type>());
  }
}

#endif
