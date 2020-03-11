//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sincos")
{
  auto std_sin = tts::vectorize<EVE_TYPE>( [](auto e) { return std::sin(double(e)); } );
  auto std_cos = tts::vectorize<EVE_TYPE>( [](auto e) { return std::cos(double(e)); } );    
  auto sincos_s =  [](auto e) { auto [s, c] = eve::sincos(e); return s; };
  auto sincos_c =  [](auto e) { auto [s, c] = eve::sincos(e); return c; };
  
  eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c); 
}
