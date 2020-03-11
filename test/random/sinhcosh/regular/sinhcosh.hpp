//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sinhcosh")
{
  auto std_sin = tts::vectorize<EVE_TYPE>( [](auto e) { return std::sinh(double(e)); } );
  auto std_cos = tts::vectorize<EVE_TYPE>( [](auto e) { return std::cosh(double(e)); } );    
  auto sinhcosh_s =  [](auto e) { auto [s, c] = eve::sinhcosh(e); return s; };
  auto sinhcosh_c =  [](auto e) { auto [s, c] = eve::sinhcosh(e); return c; };
  
  eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>()); 
  TTS_RANGE_CHECK(p, std_sin, sinhcosh_s);
  TTS_RANGE_CHECK(p, std_cos, sinhcosh_c); 
}
