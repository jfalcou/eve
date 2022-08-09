//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on prev", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return (e ==  eve::minf(eve::as<v_t>())) ?  eve::nan<v_t>() : std::nextafter(e, eve::minf(eve::as<v_t>())); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::saturated(eve::prev));
  }
  else
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return e == eve::valmin(eve::as<v_t>()) ? e : e-1; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::saturated(eve::prev));
  }
}
