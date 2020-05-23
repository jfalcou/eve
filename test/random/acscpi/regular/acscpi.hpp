//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/acscpi.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on acscpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acscpi = tts::vectorize<T>( [](auto e) { return eve::Invpi<v_t>()*std::asin(eve::rec(e)); } );

  eve::rng_producer<T> p1(eve::Valmin<v_t>(), v_t(-1));
  TTS_RANGE_CHECK(p1, std_acscpi, eve::acscpi);

  eve::rng_producer<T> p2(v_t(1), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p2, std_acscpi, eve::acscpi);
}
