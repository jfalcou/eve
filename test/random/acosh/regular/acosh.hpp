//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acosh", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acosh = tts::vectorize<T>( [](auto e) { return std::acosh(e); } );

  eve::rng_producer<T> p(v_t(1), eve::Maxlog<v_t>());
  TTS_RANGE_CHECK(p, std_acosh, eve::acosh);
}
