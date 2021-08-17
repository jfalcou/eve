//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asin", EVE_TYPE)
{
  auto std_asin = tts::vectorize<T>( [](auto e) { return std::asin(e); } );

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asin, eve::asin);
}
