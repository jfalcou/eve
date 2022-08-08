//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on csc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_csc = tts::vectorize<T>( [](auto e) { return eve::rec(std::sin(double(e))); } );

  eve::exhaustive_producer<T> p(-eve::pio_2(eve::as<v_t>()), eve::pio_2(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_csc, eve::half_circle(eve::csc));
}
