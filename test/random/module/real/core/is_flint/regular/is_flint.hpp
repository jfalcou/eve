//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_flint.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_flint", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_is_flint =  [](auto e) ->eve::logical<EVE_VALUE> { return (std::remainder(e, EVE_VALUE(1)) == EVE_VALUE(0)); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_flint, eve::is_flint);
  }
  else
  {
    auto std_is_flint =  [](auto ) ->eve::logical<EVE_VALUE> { return true; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_flint, eve::is_flint);
  }
}
