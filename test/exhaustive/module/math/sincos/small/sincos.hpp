//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/constant/pio_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sincos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sin = tts::vectorize<T>( [](auto e) { return std::sin(double(e)); } );
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(double(e)); } );
  auto sincos_s =  [](auto e) { auto [s, c] = eve::small_(eve::sincos)(e); return s; };
  auto sincos_c =  [](auto e) { auto [s, c] = eve::small_(eve::sincos)(e); return c; };

  eve::exhaustive_producer<T> p(-eve::Pio_2<v_t>(), eve::Pio_2<v_t>());
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c);
}
