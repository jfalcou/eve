//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on log", EVE_TYPE)
{
  auto std_log = [](auto e) { return std::log(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_log, eve::log);
}
