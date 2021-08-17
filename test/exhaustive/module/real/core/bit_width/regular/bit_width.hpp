//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/bit_width.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
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
