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

TTS_CASE_TPL("wide random check on coth", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_coth = tts::vectorize<T>( [](auto e) { return eve::rec(std::tanh(e)); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p, std_coth, eve::coth);

  eve::exhaustive_producer<T> p1(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p1, std_coth, eve::coth);
}
