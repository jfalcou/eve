//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>
#include <tts/tests/range.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on acosd", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acosd = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::acos(e)); } );
  double th = std::is_same_v<v_t, double> ? 4096.0 : 512.0;

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acosd, eve::acosd, th);
}
