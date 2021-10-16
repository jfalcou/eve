//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asin.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asin", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_asin = [](auto e) { return std::asin(e); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asin, eve::asin);
};