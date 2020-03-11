//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_ODD_HPP
#define IS_ODD_HPP

#include <eve/function/is_odd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check is_odd return type")
{
  TTS_EXPR_IS(eve::is_odd(EVE_TYPE(0)), eve::as_logical_t<EVE_TYPE>);
}

TTS_CASE("Check eve::is_odd behavior")
{
  TTS_EQUAL(eve::is_odd(EVE_TYPE{1}), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::is_odd(EVE_TYPE{2}), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_odd(EVE_TYPE{3}), eve::True<EVE_TYPE>());
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_odd(eve::Half<EVE_TYPE>()), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::is_odd(eve::Mzero<EVE_TYPE>()), eve::False<EVE_TYPE>());
  }
}

#endif
