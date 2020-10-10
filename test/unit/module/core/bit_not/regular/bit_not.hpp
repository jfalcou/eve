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

#include <type_traits>

TTS_CASE_TPL("Check eve::bit_not return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_not(T()), T);
}

TTS_CASE_TPL("Check eve::bit_not behavior", EVE_TYPE)
{
  TTS_IEEE_EQUAL(eve::bit_not(T(0)), (eve::allbits(eve::as<T>())));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( eve::bit_not( static_cast<T>(0x1234567890ABCDEFULL))
              , static_cast<T>(0xEDCBA9876F543210ULL)
              );

    TTS_EQUAL(eve::bit_not(T( 0)), (T(-1)));
    TTS_EQUAL(eve::bit_not(T(-1)), (T( 0)));
  }
}
