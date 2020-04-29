//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/has_single_bit.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::has_single_bit return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::has_single_bit(EVE_TYPE() )), (eve::logical<EVE_TYPE>));
}

TTS_CASE("Check eve::has_single_bit behavior")
{
  if constexpr(std::is_signed_v<EVE_TYPE>)
  {
    TTS_EQUAL(eve::has_single_bit(EVE_TYPE(-1)), eve::False<EVE_TYPE>());
  }

  TTS_EQUAL(eve::has_single_bit(EVE_TYPE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::has_single_bit(EVE_TYPE(1)), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::has_single_bit(EVE_TYPE(3)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::has_single_bit(EVE_TYPE(4)), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::has_single_bit(eve::Valmax<EVE_TYPE>()/2+1), eve::True<EVE_TYPE>());
}
