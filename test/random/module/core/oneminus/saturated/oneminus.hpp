//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on oneminus", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    auto std_oneminus = tts::vectorize<T>( [](auto e) { return e <= eve::valmin(eve::as<v_t>())+1 ? eve::valmax(eve::as<v_t>()) : v_t(1)-e; } );
    eve::rng_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_oneminus,  eve::saturated_(eve::oneminus));
 }
  else
  {
    auto std_oneminus = tts::vectorize<T>( [](auto e) { return (e <= 1) ? v_t(1)-e : v_t(0); } );
    eve::rng_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::saturated_(eve::oneminus));
  }
}
