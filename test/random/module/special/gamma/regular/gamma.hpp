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
#include <eve/function/gamma.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on gamma", EVE_TYPE)
{
  auto std_gamma = [](auto e) { return std::gamma(e); };

  eve::uniform_prng<T>  p ( eve::minlog(eve::as<EVE_VALUE>()) + 1
                          , eve::maxlog(eve::as<EVE_VALUE>()) - 1
                          );

  TTS_RANGE_CHECK(p, std_gamma, eve::gamma);
}
