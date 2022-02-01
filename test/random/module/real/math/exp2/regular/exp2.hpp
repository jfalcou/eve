//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/module/math/constant/minlog2.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp2", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::integral_value<T>)
  {
    auto std_exp2 = [](auto e) { return EVE_VALUE(std::exp2(e)); };
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-63), EVE_VALUE(63));
    TTS_RANGE_CHECK(p, std_exp2, eve::exp2);
  }
  else
  {
    auto std_exp2 = [](auto e) { return std::exp2(e); };
    eve::uniform_prng<EVE_VALUE> p(eve::minlog2(eve::as<EVE_VALUE>())+1, eve::maxlog2(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_exp2, eve::exp2);
  }
};
