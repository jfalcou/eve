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

TTS_CASE_TPL("wide random check on acospi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acospi = tts::vectorize<T>( [](auto e) { return eve::invpi(eve::as<v_t>())*std::acos(e); } );
  double th = std::is_same_v<v_t, double> ? 4096.0 : 512.0;

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acospi, eve::raw(eve::acospi), th);
}
