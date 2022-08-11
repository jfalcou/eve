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
#include <bit>

TTS_CASE_TPL("wide random check on bit_width", EVE_TYPE)
{

  using v_t = eve::element_type_t<T>;
  auto std_bit_width = tts::vectorize<T>( [](auto e) { return sizeof(v_t)*8-std::countl_zero(e); } );
  eve::exhaustive_producer<T> p(eve::zero(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_bit_width, eve::bit_width);
}
