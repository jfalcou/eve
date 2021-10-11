//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acosd", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_acosd = [](auto e) { return eve::radindeg(std::acos(e)); };
  double th = std::is_same_v<EVE_VALUE, double> ? 4096.0 : 512.0;

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK_WITH(p, std_acosd, eve::acosd, th);
};