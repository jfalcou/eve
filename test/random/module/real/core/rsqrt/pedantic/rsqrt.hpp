//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/rsqrt.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide rng check on rsqrt", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_rsqrt = [](auto e) { return EVE_VALUE(1.0l/std::sqrt((long double)e)); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::pedantic(eve::rsqrt));
};