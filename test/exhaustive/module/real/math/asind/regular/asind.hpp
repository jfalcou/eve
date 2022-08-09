//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on asind", EVE_TYPE)
{
  auto std_asind = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::asin(e)); } );

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asind, eve::asind);
}
