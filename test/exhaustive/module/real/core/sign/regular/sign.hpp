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

TTS_CASE_TPL("wide random check on sign", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    auto std_sign = tts::vectorize<T>( [](auto e) { return e > 0 ? v_t(1) : ((e < 0) ? v_t(-1) : v_t(0)); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
  else
  {
    auto std_sign = tts::vectorize<T>( [](auto e) { return e > 0 ? 1 : 0; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
}
