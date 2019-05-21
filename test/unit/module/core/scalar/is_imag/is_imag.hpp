//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_IMAG_HPP
#define IS_IMAG_HPP

#include "test.hpp"
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_imag.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_imag return type")
{
  TTS_EXPR_IS(eve::is_imag(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_imag behavior")
{
  TTS_EQUAL(eve::is_imag(Type{0}), eve::True<Type>());
  TTS_EQUAL(eve::is_imag(Type{2}), eve::False<Type>());

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_imag(eve::Inf<Type>())  , eve::False<Type>());
    TTS_EQUAL(eve::is_imag(eve::Minf<Type>()) , eve::False<Type>());
    TTS_EQUAL(eve::is_imag(eve::Nan<Type>())  , eve::False<Type>());
  }
}

#endif
