//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on acscpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acscpi = tts::vectorize<T>( [](auto e) { return eve::inv_pi(eve::as<v_t>())*std::asin(eve::rec(e)); } );

  eve::exhaustive_producer<T> p1(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p1, std_acscpi, eve::acscpi);

  eve::exhaustive_producer<T> p2(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p2, std_acscpi, eve::acscpi);
}
