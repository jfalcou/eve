//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acos.hpp>
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on acos", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_acos = [](auto e) { return std::acos(e); };

  eve::uniform_prng<EVE_VALUE> p(-1,0.999);
  TTS_RANGE_CHECK_WITH(p, std_acos, eve::raw(eve::acos), 1024.0);
};
