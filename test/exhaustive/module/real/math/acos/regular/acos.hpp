//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acos", EVE_TYPE)
{
  auto std_acos = tts::vectorize<T>( [](auto e) { return std::acos(e); } );

  eve::exhaustive_producer<T> p(-1,1);
  TTS_ULP_RANGE_CHECK(p, std_acos, eve::acos, 1024.0);
}
