//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cot", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_cot = tts::vectorize<T>( [](auto e) { return eve::rec(std::tan(double(e))); } );

  eve::exhaustive_producer<T> p(-eve::pio_2(eve::as<v_t>()), eve::pio_2(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_cot, eve::half_circle(eve::cot));
}
