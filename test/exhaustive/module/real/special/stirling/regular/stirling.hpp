//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE("wide random check on stirling")
{
  auto std_stirling = tts::vectorize<EVE_TYPE>([](auto e) { return std::stirling(e); });

  eve::exhaustive_producer<EVE_TYPE> p(eve::minlog(eve::as<EVE_VALUE>()), eve::maxlog(eve::as<EVE_VALUE>()) - 1);
  TTS_RANGE_CHECK(p, std_stirling, eve::stirling);
}
