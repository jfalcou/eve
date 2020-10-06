//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <type_traits>

TTS_CASE("Check abs return type")
{
  TTS_EXPR_IS(eve::abs(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::abs behavior")
{
  TTS_EQUAL(eve::abs(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::abs(EVE_TYPE(1)), EVE_TYPE(1));
  TTS_EQUAL(eve::abs(EVE_TYPE(2)), EVE_TYPE(2));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::abs(static_cast<EVE_TYPE>(-1)), EVE_TYPE(1));
    TTS_EQUAL(eve::abs(static_cast<EVE_TYPE>(-2)), EVE_TYPE(2));
  }
}
