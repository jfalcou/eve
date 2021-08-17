//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(e); } );

  eve::exhaustive_producer<T> p(-eve::pio_4(eve::as<v_t>()), eve::pio_4(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_cos, eve::restricted(eve::cos));
}
