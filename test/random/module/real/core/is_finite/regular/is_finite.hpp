//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_finite.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_finite", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_finite =  [](auto e)  ->eve::logical<EVE_VALUE> { return std::isfinite(e); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_finite, eve::is_finite);
  }
  else
  {
    auto std_is_finite =  [](auto ) ->eve::logical<EVE_VALUE> { return  true; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_finite, eve::is_finite);
  }
};