//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/maxlog2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp2", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp2 = tts::vectorize<T>( [](auto e) { return std::exp2(e); } );

  eve::rng_producer<T> p(eve::Minlog2<v_t>()+1, eve::Maxlog2<v_t>());
  TTS_RANGE_CHECK(p, std_exp2, eve::exp2);
}
