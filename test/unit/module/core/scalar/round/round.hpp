//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ROUND_HPP
#define ROUND_HPP


#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/nearest.hpp>
#include <eve/tags.hpp>
#include <eve/function/round.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check round return type")
{
  TTS_EXPR_IS(eve::round(Type(0)),  Type);
}

TTS_CASE("Check eve::round behavior")
{
   TTS_EQUAL(eve::round(eve::One<Type>(), eve::upward_     ), eve::ceil   (eve::One<Type>()));
   TTS_EQUAL(eve::round(eve::One<Type>(), eve::downward_   ), eve::floor  (eve::One<Type>()));
   TTS_EQUAL(eve::round(eve::One<Type>(), eve::toward_zero_), eve::trunc  (eve::One<Type>()));
   TTS_EQUAL(eve::round(eve::One<Type>(), eve::to_nearest_ ), eve::nearest(eve::One<Type>()));
   TTS_EQUAL(eve::round(eve::One<Type>()), eve::nearest(eve::One<Type>()));

   if constexpr(std::is_floating_point_v<Type>)
   {
     TTS_EQUAL(eve::round(eve::Half<Type>(), eve::upward_     ), eve::ceil(eve::Half<Type>()));
     TTS_EQUAL(eve::round(eve::Half<Type>(), eve::downward_   ), eve::floor(eve::Half<Type>()));
     TTS_EQUAL(eve::round(eve::Half<Type>(), eve::toward_zero_), eve::trunc(eve::Half<Type>()));
     TTS_EQUAL(eve::round(eve::Half<Type>(), eve::to_nearest_ ), eve::nearest(eve::Half<Type>()));
     TTS_EQUAL(eve::round(eve::Half<Type>()), eve::nearest(eve::Half<Type>()));
   }
}

#endif
