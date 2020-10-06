//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_not.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE("Check eve::bit_not return type")
{
  TTS_EXPR_IS(eve::bit_not(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::bit_not behavior")
{
  TTS_IEEE_EQUAL(eve::bit_not(EVE_TYPE(0)), (eve::allbits(eve::as<EVE_TYPE>())));

  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    TTS_EQUAL ( eve::bit_not( static_cast<EVE_TYPE>(0x1234567890ABCDEFULL))
              , static_cast<EVE_TYPE>(0xEDCBA9876F543210ULL)
              );

    TTS_EQUAL(eve::bit_not(EVE_TYPE( 0)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::bit_not(EVE_TYPE(-1)), (EVE_TYPE( 0)));
  }
}
