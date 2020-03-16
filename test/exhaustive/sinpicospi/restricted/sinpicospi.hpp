//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp>   
#include <eve/constant/pio_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"


TTS_CASE("wide random check on sinpicospi")
{
  auto std_sinpi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::sinpi(double(e)); } );
  auto std_cospi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::cospi(double(e)); } );    
  auto sinpicospi_s =  [](auto e) { auto [s, c] = eve::small_(eve::sinpicospi)(e); return s; };
  auto sinpicospi_c =  [](auto e) { auto [s, c] = eve::small_(eve::sinpicospi)(e); return c; };
  
  eve::exhaustive_producer<EVE_TYPE> p(-EVE_VALUE(0.25), EVE_VALUE(0.25));
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c); 
}
