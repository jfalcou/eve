//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sign", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::signed_value<T>)
  {
    auto std_sign = [](auto e) { return e > 0 ? EVE_VALUE(1) : ((e < 0) ? EVE_VALUE(-1) : EVE_VALUE(0)); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
  else
  {
    auto std_sign = [](auto e) { return e > 0 ? EVE_VALUE(1) : EVE_VALUE(0); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
};