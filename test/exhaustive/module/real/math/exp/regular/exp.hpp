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

TTS_CASE_TPL("wide random check on exp", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp = tts::vectorize<T>( [](auto e) { return std::exp(e); } );

  eve::exhaustive_producer<T> p(eve::minlog(eve::as<v_t>())+1, eve::maxlog(eve::as<v_t>())-1);
  TTS_RANGE_CHECK(p, std_exp, eve::exp);
}
