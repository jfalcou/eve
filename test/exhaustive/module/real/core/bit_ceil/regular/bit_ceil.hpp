//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
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
