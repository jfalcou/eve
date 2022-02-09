//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on rsqrt", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_rsqrt = [](auto e) { return EVE_VALUE(1)/std::sqrt(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::smallestposval(eve::as<EVE_VALUE>()), EVE_VALUE(eve::valmax(eve::as<float>())));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::rsqrt);
};