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

TTS_CASE_TPL("wide random check on abs", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_abs = tts::vectorize<T>( [](auto e) { return (e < 0) ? -e : e; } );
    eve::exhaustive_producer<T> p(-1,1);
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto std_abs = tts::vectorize<T>( [](auto e) { return (e < 0) ? -e : e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
  else
  {
    auto std_abs = tts::vectorize<T>( [](auto e) { return e; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
}
