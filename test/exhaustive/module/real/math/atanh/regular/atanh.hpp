//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on atanh", EVE_TYPE)
{
  auto std_atanh = tts::vectorize<T>( [](auto e) { return std::atanh(e); } );

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_RANGE_CHECK(p, std_atanh, eve::atanh);
}
