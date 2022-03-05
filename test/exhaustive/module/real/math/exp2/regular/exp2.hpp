//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/concept/value.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp2", EVE_TYPE)
{

  using v_t = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    auto std_exp2 = tts::vectorize<T>( [](auto e) { return v_t(std::exp2(e)); } );
    eve::exhaustive_producer<T> p(v_t(-63), v_t(63));
    TTS_RANGE_CHECK(p, std_exp2, eve::exp2);
  }
  else
  {
  auto std_exp2 = tts::vectorize<T>( [](auto e) { return std::exp2(e); } );
    eve::exhaustive_producer<T> p(eve::minlog2(eve::as<v_t>()), eve::maxlog2(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_exp2, eve::exp2);
  }
}
