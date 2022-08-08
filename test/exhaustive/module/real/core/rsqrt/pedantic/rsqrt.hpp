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

TTS_CASE_TPL("wide exhaustive check on rsqrt", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_rsqrt = tts::vectorize<T>( [](auto e) { return v_t(1.0l/std::sqrt((long double)e)); } );

  eve::exhaustive_producer<T> p(v_t(0), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::pedantic(eve::rsqrt));
}
