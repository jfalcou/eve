//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sincos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sin = tts::vectorize<T>( [](auto e) { return std::sin(double(e)); } );
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(double(e)); } );
  auto sincos_s =  [](auto e) { auto [s, c] = eve::big(eve::sincos)(e); return s; };
  auto sincos_c =  [](auto e) { auto [s, c] = eve::big(eve::sincos)(e); return c; };

  eve::exhaustive_producer<T> p(0, eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c);
}
