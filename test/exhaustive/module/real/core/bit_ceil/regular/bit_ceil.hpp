//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on bit_ceil", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_bit_ceil = tts::vectorize<T>( [](auto e) { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); } );
    eve::exhaustive_producer<T> p(v_t(0), eve::valmax(eve::as<v_t>())/4);
    TTS_RANGE_CHECK(p, std_bit_ceil, eve::bit_ceil);
  }
  else
  {
    auto std_bit_ceil = tts::vectorize<T>( [](auto e) { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), (1ul << (sizeof(v_t)*8-2)));
    TTS_RANGE_CHECK(p, std_bit_ceil, eve::bit_ceil);
  }
}
