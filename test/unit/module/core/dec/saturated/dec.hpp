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
#include <eve/function/saturated.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::dec) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dec)(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::saturated_(eve::dec) behavior")
{
  using eve::saturated_;

  TTS_EQUAL(saturated_(eve::dec)(eve::Valmin<EVE_TYPE>()), eve::Valmin<EVE_TYPE>());
  TTS_EQUAL(saturated_(eve::dec)(EVE_TYPE(1)), (EVE_TYPE( 0)) );
  TTS_EQUAL(saturated_(eve::dec)(EVE_TYPE(2)), (EVE_TYPE( 1)) );

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(saturated_(eve::dec)(EVE_TYPE(0)), (EVE_TYPE(-1)) );
  }
  else
  {
    TTS_EQUAL(saturated_(eve::dec)(EVE_TYPE(0)), (EVE_TYPE(0)) );
  }
}
