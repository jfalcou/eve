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

TTS_CASE_TPL("wide random check on bit_mask", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_bit_mask = tts::vectorize<T>( [](auto e) { return e ? eve::allbits(eve::as<v_t>()) : eve::zero(eve::as<v_t>()); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>())+1, eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_bit_mask, eve::bit_mask);
}
