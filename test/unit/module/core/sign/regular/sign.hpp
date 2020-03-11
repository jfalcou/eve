//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sign return type")
{
  TTS_EXPR_IS(eve::sign(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::sign behavior")
{
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::sign(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(-1)));
  }

  TTS_EQUAL(eve::sign(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::sign(EVE_TYPE(2)), (EVE_TYPE(1)));
}
