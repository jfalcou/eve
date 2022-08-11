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

TTS_CASE_TPL("wide random check on exp10", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp10 = tts::vectorize<T>( [](auto e) { return ::exp10l(e); } );

  eve::exhaustive_producer<T> p(eve::minlog10(eve::as<v_t>()), eve::maxlog10(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_exp10, eve::pedantic(eve::exp10));
}
