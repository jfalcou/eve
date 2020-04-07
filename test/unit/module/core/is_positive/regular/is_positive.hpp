//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_POSITIVE_HPP
#define IS_POSITIVE_HPP

#include <eve/function/is_positive.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check is_positive return type")
{
  TTS_EXPR_IS(eve::is_positive(EVE_TYPE()), eve::as_logical_t<EVE_TYPE>);
}

TTS_CASE("Check eve::is_positive behavior")
{
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_positive(EVE_TYPE(-1)), eve::False<EVE_TYPE>());
  }
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_positive(eve::Zero<EVE_TYPE>()), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::is_positive(eve::Mzero<EVE_TYPE>()), eve::False<EVE_TYPE>());
  }
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_positive(eve::Nan<EVE_TYPE>()), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::is_positive(-eve::Nan<EVE_TYPE>()), eve::True<EVE_TYPE>());
  }
  TTS_EQUAL(eve::is_positive(EVE_TYPE(0)), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::is_positive(EVE_TYPE(3)), eve::True<EVE_TYPE>());
}

#endif
