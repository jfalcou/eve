//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cosh", EVE_TYPE)
{
  auto std_cosh = [](auto e) { return std::cosh(e); };

  eve::uniform_prng<EVE_VALUE> p(-eve::maxlog(eve::as<EVE_VALUE>()), eve::maxlog(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_cosh, eve::cosh);
}
