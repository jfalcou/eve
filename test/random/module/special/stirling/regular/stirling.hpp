//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/stirling.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on stirling")
{
  auto std_stirling = [](auto e) { return std::stirling(e); };
  auto eve_stirling = [](auto e) { return eve::stirling(e); };

  eve::uniform_prng<EVE_TYPE> p ( eve::minlog(eve::as<EVE_VALUE>())
                                , eve::maxlog(eve::as<EVE_VALUE>()) - 1
                                );

  TTS_RANGE_CHECK(p, std_stirling, eve_stirling);
}
