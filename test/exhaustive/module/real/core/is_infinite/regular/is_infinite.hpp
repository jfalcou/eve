//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/traits/as_logical.hpp>
#include <eve/module/core.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_infinite", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t = eve::as_logical_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_infinite = tts::vectorize<l_t>( [](auto e) { return std::isinf(e); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_infinite, eve::is_infinite);
  }
  else
  {
    auto std_is_infinite = tts::vectorize<l_t>( [](auto ) { return false; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_is_infinite, eve::is_infinite);
  }
}
