//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sign", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    auto std_sign = tts::vectorize<T>( [](auto e) { return e > 0 ? v_t(1) : ((e < 0) ? v_t(-1) : v_t(0)); } );
    eve::rng_producer<T> p(eve::Valmin<v_t>()+1, eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
  else
  {
    auto std_sign = tts::vectorize<T>( [](auto e) { return e > 0 ? 1 : 0; } );
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_sign, eve::sign);
  }
}
