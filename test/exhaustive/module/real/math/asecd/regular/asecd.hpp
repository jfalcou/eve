//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================

#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on asecd", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_asecd = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::acos(eve::rec(e))); } );

  eve::exhaustive_producer<T> p1(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p1, std_asecd, eve::asecd);

  eve::exhaustive_producer<T> p2(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p2, std_asecd, eve::asecd);
}
