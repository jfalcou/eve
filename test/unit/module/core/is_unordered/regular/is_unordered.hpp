//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_UNORDERED_HPP
#define IS_UNORDERED_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_unordered.hpp>
#include <type_traits>

TTS_CASE("Check is_unordered return type")
{
  TTS_EXPR_IS(eve::is_unordered(EVE_TYPE(), EVE_TYPE()), eve::as_logical_t<EVE_TYPE>);
}

TTS_CASE("Check eve::is_unordered behavior on arithmetic")
{
  TTS_EQUAL(eve::is_unordered(EVE_TYPE(1), EVE_TYPE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_unordered(EVE_TYPE(3), EVE_TYPE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_unordered(EVE_TYPE(1), EVE_TYPE(3)), eve::False<EVE_TYPE>());

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_unordered(eve::Nan<EVE_TYPE>(), EVE_TYPE(3)), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::is_unordered(EVE_TYPE(3), eve::Nan<EVE_TYPE>()), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::is_unordered(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()), eve::True<EVE_TYPE>());
  }
}

TTS_CASE("Check eve::is_unordered behavior on logical")
{
  TTS_EQUAL(eve::is_unordered(eve::logical<EVE_TYPE>(1), eve::logical<EVE_TYPE>(0)), eve::False<EVE_TYPE>());
}

#endif

