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

TTS_CASE_TPL("wide random check on asinpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_asinpi = tts::vectorize<T>( [](auto e) { return eve::inv_pi(eve::as<v_t>())*std::asin(e); } );

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asinpi, eve::asinpi);
}
