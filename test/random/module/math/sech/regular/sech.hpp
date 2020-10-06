//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/function/cosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sech", EVE_TYPE)
{
  auto std_sech = [](auto e) -> EVE_VALUE { return EVE_VALUE(1)/eve::cosh(double(e)); };
  auto max = eve::maxlog(eve::as<EVE_VALUE>())-EVE_VALUE(1);
  eve::uniform_prng<EVE_VALUE> p(-max, max);
  TTS_RANGE_CHECK(p, std_sech, eve::sech);
}
