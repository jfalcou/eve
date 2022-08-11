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

TTS_CASE_TPL("wide random check on sincos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sin = tts::vectorize<T>( [](auto e) { return std::sin(double(e)); } );
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(double(e)); } );
  auto sincos_s =  [](auto e) { auto [s, c] = eve::half_circle(eve::sincos)(e); return s; };
  auto sincos_c =  [](auto e) { auto [s, c] = eve::half_circle(eve::sincos)(e); return c; };

  eve::exhaustive_producer<T> p(-eve::pio_2(eve::as<v_t>()), eve::pio_2(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c);
}
