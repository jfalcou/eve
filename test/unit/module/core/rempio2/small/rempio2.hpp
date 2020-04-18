//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rempio2.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("wide random check on rempio2")
{

  EVE_VALUE z = EVE_VALUE(1);
 for(int i=1; i <10 ; ++i)
 {
   auto [n, x, dx] = eve::small_(eve::rempio2)(EVE_TYPE(z));
   auto [nn, xx, dxx] = eve::rem_pio2(z);
   TTS_ULP_EQUAL(x ,  EVE_TYPE(xx)   , 0.5 );
   TTS_ULP_EQUAL(n ,  EVE_TYPE(nn)   , 0.5 );
   z/= EVE_VALUE(10);
 }
}
