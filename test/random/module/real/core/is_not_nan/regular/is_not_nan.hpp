//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_not_nan.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_not_nan", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_is_not_nan =  [](auto e) ->eve::logical<EVE_VALUE> { return e == e; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_not_nan, eve::is_not_nan);
  }
  else
  {
    auto std_is_not_nan =  [](auto ) ->eve::logical<EVE_VALUE> { return true; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_not_nan, eve::is_not_nan);
  }
}
