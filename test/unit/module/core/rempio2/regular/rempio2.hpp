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
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on rempio2")
{
  auto std_rempio2_n = tts::vectorize<EVE_TYPE>( [](auto e) { auto [n, x, dx] = eve::rem_pio2(e); return n; } );
  auto std_rempio2_x = tts::vectorize<EVE_TYPE>( [](auto e) { auto [n, x, dx] = eve::rem_pio2(e); return x; } );
  auto rempio2_n =  [](auto e) { auto [n, x, dx] = eve::rempio2(e); return n; };
  auto rempio2_x =  [](auto e) { auto [n, x, dx] = eve::rempio2(e); return x; };

  EVE_TYPE z = EVE_TYPE( 0.05); 
 for(int i=0; i <10 ; ++i)
 {
   TTS_ULP_EQUAL(rempio2_x(EVE_TYPE(z)) , std_rempio2_x(EVE_TYPE(z))   , 0.5 );
   TTS_ULP_EQUAL(rempio2_n(EVE_TYPE(z)) , std_rempio2_n(EVE_TYPE(z))   , 0.5 );     
   z*= EVE_VALUE(10); 
 }
}

