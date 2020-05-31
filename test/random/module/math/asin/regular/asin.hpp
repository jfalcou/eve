//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asin", EVE_TYPE)
{
  auto std_asin = tts::vectorize<T>( [](auto e) { return std::asin(e); } );

  eve::rng_producer<T> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asin, eve::asin);
}
