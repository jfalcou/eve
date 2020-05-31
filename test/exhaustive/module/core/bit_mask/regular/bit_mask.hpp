//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_mask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on bit_mask", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_bit_mask = tts::vectorize<T>( [](auto e) { return e ? eve::Allbits<v_t>() : eve::Zero<v_t>(); } );

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>()+1, eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_bit_mask, eve::bit_mask);
}
