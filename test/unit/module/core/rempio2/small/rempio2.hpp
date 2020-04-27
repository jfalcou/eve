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

TTS_CASE_TPL("wide random check on rempio2", EVE_TYPE)
{

  v_t z = v_t(1);
 for(int i=1; i <10 ; ++i)
 {
   auto [n, x, dx] = eve::small_(eve::rempio2)(T(z));
   auto [nn, xx, dxx] = eve::rem_pio2(z);
   TTS_ULP_EQUAL(x ,  T(xx)   , 0.5 );
   TTS_ULP_EQUAL(n ,  T(nn)   , 0.5 );
   z/= v_t(10);
 }
}
