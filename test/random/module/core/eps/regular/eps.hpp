//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/eps.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on eps", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_eps = tts::vectorize<T>( [](auto e) { return (e > 0 ? e : -e)*eve::Eps<v_t>()/2; } );
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_eps, eve::eps);
  }
  else
  {
    auto std_eps = tts::vectorize<T>( [](auto ) { return  v_t(1); } );
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_eps, eve::eps);
  }
}
