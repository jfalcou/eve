//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_exp = [](auto e) { return std::exp(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::minlog(eve::as<EVE_VALUE>())+1, eve::maxlog(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_exp, eve::exp);
};