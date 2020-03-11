//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_not.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_not return type")
{
  TTS_EXPR_IS(eve::bit_not(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::bit_not behavior")
{
  TTS_IEEE_EQUAL(eve::bit_not(EVE_TYPE(0)), (eve::Allbits<EVE_TYPE>()));

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL ( eve::bit_not( static_cast<EVE_TYPE>(0x1234567890ABCDEFULL))
              , static_cast<EVE_TYPE>(0xEDCBA9876F543210ULL)
              );

    TTS_EQUAL(eve::bit_not(EVE_TYPE( 0)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::bit_not(EVE_TYPE(-1)), (EVE_TYPE( 0)));
  }
}

