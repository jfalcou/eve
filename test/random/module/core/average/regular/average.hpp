//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on average")
{
  auto std_average = [](auto e) { return std::midpoint(e,  one(eve::as(e))); } );
  auto  my_average =  [](auto e) {
    static int i = 0;
    std::cout << ++i <<  "-> " << e <<  std::endl;
    return eve::average(e,  one(eve::as(e))); };
  if constexpr(eve::floating_value<T>)
  {

    eve::piecewise_rng_producer<T> p(1, 4, 2); //eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 2);
  }
  else
  {
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 0.5);
  }
}
