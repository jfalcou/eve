//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::dec return type")
{
  TTS_EXPR_IS(eve::dec(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::dec behavior")
{
  TTS_EQUAL(eve::dec(EVE_TYPE(0)), (EVE_TYPE(-1)) );
  TTS_EQUAL(eve::dec(EVE_TYPE(1)), (EVE_TYPE( 0)) );
  TTS_EQUAL(eve::dec(EVE_TYPE(2)), (EVE_TYPE( 1)) );

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::dec(EVE_TYPE(-2)), (EVE_TYPE(-3)));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::dec(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(-1)));
  }
}
