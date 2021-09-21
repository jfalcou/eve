//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on average", EVE_TYPE)
{
  auto std_average = [](auto e) { return std::midpoint(e,  one(eve::as(e))); };
  auto  my_average =  [](auto e) { return eve::average(e,  one(eve::as(e))); };
  if constexpr(eve::floating_value<T>)
  {

    eve::uniform_prng_producer<T> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 2);
  }
  else
  {
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 0.5);
  }
}
