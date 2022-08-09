//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on inc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_inc = tts::vectorize<T>( [](auto e) { return e == eve::valmax(eve::as<v_t>()) ? eve::valmin(eve::as<v_t>()) : e+1; } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_inc, eve::inc);
}
