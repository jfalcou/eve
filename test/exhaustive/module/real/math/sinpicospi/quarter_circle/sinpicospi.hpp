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

TTS_CASE_TPL("wide random check on sinpicospi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_sinpi = tts::vectorize<T>( [](auto e) { return eve::sinpi(double(e)); } );
  auto std_cospi = tts::vectorize<T>( [](auto e) { return eve::cospi(double(e)); } );
  auto sinpicospi_s =  [](auto e) { auto [s, c] = eve::half_circle(eve::sinpicospi)(e); return s; };
  auto sinpicospi_c =  [](auto e) { auto [s, c] = eve::half_circle(eve::sinpicospi)(e); return c; };

  eve::exhaustive_producer<T> p(-v_t(0.25), v_t(0.25));
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c);
}
