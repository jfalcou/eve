//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
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
  eve::rng_producer<T> p(eve::Zero<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_bit_width, eve::bit_width);
}
