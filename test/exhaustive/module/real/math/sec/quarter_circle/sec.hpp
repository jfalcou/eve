//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sec", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sec = tts::vectorize<T>( [](auto e) { return 1/std::cos(e); } );

  eve::exhaustive_producer<T> p(-eve::pio_4(eve::as<v_t>()), eve::pio_4(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sec, eve::quarter_circle(eve::sec));
}
