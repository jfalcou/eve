//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_REAL_HPP
#define IS_NOT_REAL_HPP

#include "test.hpp"
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_not_real.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_not_real return type")
{
  TTS_EXPR_IS(eve::is_not_real(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_real behavior")
{
  TTS_EQUAL(eve::is_not_real(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_not_real(Type{2}), eve::False<Type>());

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_not_real(eve::Inf<Type>())  , eve::False<Type>());
    TTS_EQUAL(eve::is_not_real(eve::Minf<Type>()) , eve::False<Type>());
    TTS_EQUAL(eve::is_not_real(eve::Nan<Type>())  , eve::False<Type>());
  }
}

#endif
