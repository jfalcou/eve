//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/arg.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/math/constant/pi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on arg", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_arg = [](auto e) { return eve::is_negative(e) ? eve::pi(eve::as<EVE_VALUE>()) : EVE_VALUE(0);};

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_arg, eve::pedantic(eve::arg));
};
