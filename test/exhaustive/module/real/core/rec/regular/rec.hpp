//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/concept/value.hpp>
#include <eve/module/core.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on rec", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    auto std_rec = tts::vectorize<T>( [](auto e) { return e ? v_t(1)/e : eve::valmax(eve::as<v_t>()); } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
  else
  {
    auto std_rec = tts::vectorize<T>( [](auto e) { return v_t(1)/e; } );

    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
}
