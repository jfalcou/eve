//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on expm1", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_expm1 = tts::vectorize<T>( [](auto e) { return std::expm1(e); } );

  eve::exhaustive_producer<T> p(eve::minlog(eve::as<v_t>()), eve::maxlog(eve::as<v_t>())-1);
  TTS_RANGE_CHECK(p, std_expm1, eve::expm1);
}
