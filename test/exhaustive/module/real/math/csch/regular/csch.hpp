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

TTS_CASE_TPL("wide random check on csch", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_csch = tts::vectorize<T>( [](auto e) { return eve::rec(std::sinh(e)); } );

  eve::exhaustive_producer<T> p(-eve::maxlog(eve::as<v_t>())+1, eve::maxlog(eve::as<v_t>())-1);
  TTS_RANGE_CHECK(p, std_csch, eve::csch);
}
