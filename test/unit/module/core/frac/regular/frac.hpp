//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frac.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::frac return type")
{
  TTS_EXPR_IS(eve::frac(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::frac behavior")
{
  TTS_EQUAL(eve::frac(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::frac(EVE_TYPE(2)), EVE_TYPE(0));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::frac(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(0)) );
    TTS_EQUAL(eve::frac(static_cast<EVE_TYPE>(1)) , (EVE_TYPE(0)) );
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::frac(EVE_TYPE(-3/2.)), EVE_TYPE(-0.5));
    TTS_EQUAL(eve::frac(EVE_TYPE( 3/2.)), EVE_TYPE( 0.5));

    TTS_ULP_EQUAL(eve::frac(EVE_TYPE( 4/3.)), (EVE_TYPE( 1/3.)), 0.5);
    TTS_ULP_EQUAL(eve::frac(EVE_TYPE(-4/3.)), (EVE_TYPE(-1/3.)), 0.5);
  }
}
