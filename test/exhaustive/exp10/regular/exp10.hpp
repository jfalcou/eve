//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/maxlog10.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on exp10", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp10 = tts::vectorize<T>( [](auto e) { return ::exp10(e); } );

  eve::exhaustive_producer<T> p(eve::Minlog10<v_t>()+1, eve::Maxlog10<v_t>()-1);
  TTS_RANGE_CHECK(p, std_exp10, eve::exp10);
}
