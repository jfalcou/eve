//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acospi.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on acospi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acospi = tts::vectorize<T>( [](auto e) { return eve::Invpi<v_t>()*std::acos(e); } );

  eve::exhaustive_producer<T> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acospi, eve::raw_(eve::acospi), 1024);
}
