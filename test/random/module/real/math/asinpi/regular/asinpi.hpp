//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/module/math/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asinpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_asinpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::asin(e); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asinpi, eve::asinpi);
};
