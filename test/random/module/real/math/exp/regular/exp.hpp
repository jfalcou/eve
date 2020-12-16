//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp", EVE_TYPE)
{
  auto std_exp = [](auto e) { return std::exp(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::minlog(eve::as<EVE_VALUE>())+1, eve::maxlog(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_exp, eve::exp);
}
