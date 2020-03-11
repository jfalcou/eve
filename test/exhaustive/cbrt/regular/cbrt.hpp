//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/ldexp.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on cbrt")
{
  auto std_cbrt = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(std::cbrt(double(e))); } );

  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_cbrt, eve::cbrt); 
}
