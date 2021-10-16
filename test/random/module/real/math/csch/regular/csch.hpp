//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on csch", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_csch = [](auto e) { return eve::rec(std::sinh(e)); };

  eve::uniform_prng<EVE_VALUE> p(-eve::maxlog(eve::as<EVE_VALUE>())+1, eve::maxlog(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_csch, eve::csch);
};