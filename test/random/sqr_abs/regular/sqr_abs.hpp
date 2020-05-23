//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr_abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sqr_abs", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sqr_abs = tts::vectorize<T>( [](auto e) { return e*e; } );

  eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_sqr_abs, eve::sqr_abs);
}
