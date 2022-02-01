//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/atanpi.hpp>
#include <eve/module/math/constant/invpi.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on atanpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_atanpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::atan(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_atanpi, eve::atanpi);
};
