//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/allbits.hpp>

TTS_CASE_TPL("Check operator~ return type", EVE_TYPE)
{
  TTS_EXPR_IS(~T(), T);
}

TTS_CASE_TPL("Check operator~ behavior", EVE_TYPE)
{
  TTS_IEEE_EQUAL(~T(0), (eve::allbits(eve::as<T>())));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL (  ~static_cast<T>(0x1234567890ABCDEFULL)
              ,   static_cast<T>(0xEDCBA9876F543210ULL)
              );

    TTS_EQUAL(~T( 0), T(-1));
    TTS_EQUAL(~T(-1), T( 0));
  }
}
