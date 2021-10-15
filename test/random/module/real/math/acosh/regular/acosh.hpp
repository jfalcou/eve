//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acosh", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_acosh = [](auto e) { return std::acosh(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(1), eve::maxlog(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_acosh, eve::acosh);
};