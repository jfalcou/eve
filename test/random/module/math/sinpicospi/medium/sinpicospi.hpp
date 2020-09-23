//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sinpicospi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_sinpi = tts::vectorize<T>( [](auto e) { return eve::sinpi(double(e)); } );
  auto std_cospi = tts::vectorize<T>( [](auto e) { return eve::cospi(double(e)); } );
  auto sinpicospi_s =  [](auto e) { auto [s, c] = eve::medium(eve::sinpicospi)(e); return s; };
  auto sinpicospi_c =  [](auto e) { auto [s, c] = eve::medium(eve::sinpicospi)(e); return c; };

  eve::rng_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c);
}
