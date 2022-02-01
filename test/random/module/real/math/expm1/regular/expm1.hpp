//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on expm1", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_expm1 = [](auto e) { return std::expm1(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::minlog(eve::as<EVE_VALUE>()), eve::maxlog(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_expm1, eve::expm1);
};
