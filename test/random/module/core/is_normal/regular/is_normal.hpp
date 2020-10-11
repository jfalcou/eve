//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_normal.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_normal", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_is_normal =  [](auto e)  ->eve::logical<EVE_VALUE> { return std::fpclassify(e) == FP_NORMAL; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_normal, eve::is_normal);
  }
  else
  {
    auto std_is_normal =  [](auto e)  ->eve::logical<EVE_VALUE> { return e !=  EVE_VALUE(0); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_normal, eve::is_normal);
  }
}
