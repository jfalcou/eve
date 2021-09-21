//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp = tts::vectorize<T>( [](auto e) { return std::exp(e); } );

  eve::exhaustive_producer<T> p(eve::minlog(eve::as<v_t>()), eve::maxlog(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_exp, eve::pedantic(eve::exp));
}
