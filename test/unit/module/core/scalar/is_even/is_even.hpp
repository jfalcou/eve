//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EVEN_HPP
#define IS_EVEN_HPP

#include <eve/function/scalar/is_even.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_even return type")
{
  TTS_EXPR_IS(eve::is_even(Type(0)), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_even behavior")
{
  TTS_EQUAL(eve::is_even(Type{1}), eve::False<Type>());
  TTS_EQUAL(eve::is_even(Type{2}), eve::True<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_even(eve::Half<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_even(eve::Inf<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_even(eve::Minf<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_even(eve::Nan<Type>()), eve::False<Type>());
  }
}

#endif
