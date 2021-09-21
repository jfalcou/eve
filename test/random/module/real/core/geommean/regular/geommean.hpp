//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/geommean.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on geommean", EVE_TYPE)
{
  auto std_geommean = [](auto e) { return std::midpoint(e,  one(eve::as(e))); };
  auto  my_geommean =  [](auto e) { return eve::geommean(e,  one(eve::as(e))); };
  if constexpr(eve::floating_value<T>)
  {

    eve::uniform_prng_producer<T> p(EVE_VALUE(0)), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_geommean, my_geommean, 2);
  }
  else
  {
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_geommean, my_geommean, 0.5);
  }
}
