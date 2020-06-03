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
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on average", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_average = tts::vectorize<T>( [](auto e) { return std::midpoint(e,  eve::One(eve::as(e))); } );
  auto  my_average =  [](auto e) {
    static int i = 0;
    std::cout << ++i <<  "-> " << e <<  std::endl;
    return eve::average(e,  eve::One(eve::as(e))); };
  if constexpr(eve::floating_value<T>)
  {

    eve::piecewise_rng_producer<T> p(1, 4, 2); //eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 2);
  }
  else
  {
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_ULP_RANGE_CHECK(p, std_average, my_average, 0.5);
  }
}
