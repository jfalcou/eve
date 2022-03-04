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

TTS_CASE_TPL("wide random check on atanpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_atanpi = tts::vectorize<T>( [](auto e) { return eve::invpi(eve::as<v_t>())*std::atan(e); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_atanpi, eve::atanpi);
}
