//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IROUND_HPP
#define IROUND_HPP

#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/nearest.hpp>
#include <eve/tags.hpp>
#include <eve/function/iround.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check iround return type") { TTS_EXPR_IS(eve::iround(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE("Check eve::iround behavior")
{
  TTS_EQUAL(eve::iround(eve::One<Type>(), eve::upward_), eve::iceil(eve::One<Type>()));
  TTS_EQUAL(eve::iround(eve::One<Type>(), eve::downward_), eve::ifloor(eve::One<Type>()));
  TTS_EQUAL(eve::iround(eve::One<Type>(), eve::toward_zero_), eve::itrunc(eve::One<Type>()));
  TTS_EQUAL(eve::iround(eve::One<Type>(), eve::to_nearest_), eve::inearest(eve::One<Type>()));
  TTS_EQUAL(eve::iround(eve::One<Type>()), eve::inearest(eve::One<Type>()));

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::iround(eve::Half<Type>(), eve::upward_), eve::iceil(eve::Half<Type>()));
    TTS_EQUAL(eve::iround(eve::Half<Type>(), eve::downward_), eve::ifloor(eve::Half<Type>()));
    TTS_EQUAL(eve::iround(eve::Half<Type>(), eve::toward_zero_), eve::itrunc(eve::Half<Type>()));
    TTS_EQUAL(eve::iround(eve::Half<Type>(), eve::to_nearest_), eve::inearest(eve::Half<Type>()));
    TTS_EQUAL(eve::iround(eve::Half<Type>()), eve::inearest(eve::Half<Type>()));
  }
}

#endif
