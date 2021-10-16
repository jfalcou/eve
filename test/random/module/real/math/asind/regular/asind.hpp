//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/radindeg.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asind", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_asind = [](auto e) { return eve::radindeg(std::asin(e)); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asind, eve::asind);
};