//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_exp = tts::vectorize<T>( [](auto e) { return std::exp(e); } );

  eve::rng_producer<T> p(eve::minlog(eve::as<v_t>())+1, eve::maxlog(eve::as<v_t>())-1);
  TTS_RANGE_CHECK(p, std_exp, eve::exp);
}
