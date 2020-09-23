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

TTS_CASE_TPL("wide random check on pow_abs", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_pow_abs = tts::vectorize<T>( [](auto e) { return std::pow(std::abs(e),  100*iota(eve::as(e))); } );
  auto  my_pow_abs =  [](auto e) {  return eve::pow_abs(e,  iota(eve::as(e))); };

 eve::rng_producer<T> p(eve::zero(eve::as<v_t>()), v_t(100)));
  TTS_RANGE_CHECK(p, std_powabs, my_pow_abs);

}
