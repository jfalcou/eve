//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on to int", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_trunc = [](auto e) { return std::trunc(e); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_trunc, eve::trunc);
  }
  else
  {
    auto std_trunc = [](auto e) { return e; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_trunc, eve::trunc);
  }
};