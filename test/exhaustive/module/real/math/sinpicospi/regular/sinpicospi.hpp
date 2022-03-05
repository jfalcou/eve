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

TTS_CASE_TPL("wide random check on sinpicospipi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_sinpi = tts::vectorize<T>( [](auto e) { return eve::sinpi(double(e)); } );
  auto std_cospi = tts::vectorize<T>( [](auto e) { return eve::cospi(double(e)); } );
  auto sinpicospi_s =  [](auto e) { auto [s, c] = eve::sinpicospi(e); return s; };
  auto sinpicospi_c =  [](auto e) { auto [s, c] = eve::sinpicospi(e); return c; };

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c);
}
