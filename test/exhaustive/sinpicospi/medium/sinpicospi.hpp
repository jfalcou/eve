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
#include <eve/function/sinpi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sinpicospi")
{
  auto std_sinpi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::sinpi(double(e)); } );
  auto std_cospi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::cospi(double(e)); } );    
  auto sinpicospi_s =  [](auto e) { auto [s, c] = eve::medium_(eve::sinpicospi)(e); return s; };
  auto sinpicospi_c =  [](auto e) { auto [s, c] = eve::medium_(eve::sinpicospi)(e); return c; };
  
  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c); 
}
