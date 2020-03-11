//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_pow2 return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::is_pow2(EVE_TYPE() )), (eve::logical<EVE_TYPE>));
}

TTS_CASE("Check eve::is_pow2 behavior")
{
  if constexpr(std::is_signed_v<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_pow2(EVE_TYPE(-1)), eve::False<EVE_TYPE>());
  }

  TTS_EQUAL(eve::is_pow2(EVE_TYPE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_pow2(EVE_TYPE(1)), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::is_pow2(EVE_TYPE(3)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_pow2(EVE_TYPE(4)), eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::is_pow2(eve::Valmax<EVE_TYPE>()/2+1), eve::True<EVE_TYPE>());
}
