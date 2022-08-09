//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acoth", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acoth = tts::vectorize<T>( [](auto e) { return std::tanh(eve::rec(e)); } );

  eve::exhaustive_producer<T> p1(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p1, std_acoth, eve::acoth);

  eve::exhaustive_producer<T> p2(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p2, std_acoth, eve::acoth);
}
