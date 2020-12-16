//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_floor.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
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
