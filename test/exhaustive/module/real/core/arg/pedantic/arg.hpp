//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on arg", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_arg = tts::vectorize<T>( [](auto e) { return eve::is_negative(e) ? eve::pi(eve::as<v_t>()) : v_t(0); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_arg, eve::pedantic(eve::arg));
}
