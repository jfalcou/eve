//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  auto std_cot = tts::vectorize<T>( [](auto e) { return 1/std::tan(double(e)); } );

  if constexpr(eve::platform::supports_denormals)
  {
    eve::exhaustive_producer<T> p(-eve::pio_4(eve::as<v_t>()), eve::pio_4(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_cot, eve::quarter_circle(eve::cot));
  }
  else
  {
    eve::exhaustive_producer<T> p(eve::smallestposval(eve::as<v_t>()), eve::pio_4(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_cot, eve::quarter_circle(eve::cot));
  }
}
