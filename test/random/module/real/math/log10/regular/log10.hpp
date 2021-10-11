//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/log10.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on log10", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_log10 = [](auto e) { return std::log10(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_log10, eve::log10);
};