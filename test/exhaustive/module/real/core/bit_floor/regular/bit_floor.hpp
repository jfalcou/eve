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

TTS_CASE_TPL("wide random check on bit_floor", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_bit_floor = tts::vectorize<T>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::exhaustive_producer<T> p(v_t(0), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto std_bit_floor = tts::vectorize<T>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::exhaustive_producer<T> p(v_t(0), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
  else
  {
    auto std_bit_floor = tts::vectorize<T>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
}
