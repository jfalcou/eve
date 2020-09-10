//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/function/stirling.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE("wide random check on stirling")
{
  auto std_stirling = tts::vectorize<EVE_TYPE>([](auto e) { return std::stirling(e); });

  eve::exhaustive_producer<EVE_TYPE> p(eve::Minlog<EVE_VALUE>(), eve::maxlog(eve::as<EVE_VALUE>()) - 1);
  TTS_RANGE_CHECK(p, std_stirling, eve::stirling);
}
