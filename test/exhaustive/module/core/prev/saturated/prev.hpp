//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/minf.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>
#include <type_traits>

TTS_CASE_TPL("wide exhaustive check on prev", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return (e ==  eve::minf(eve::as<v_t>())) ?  eve::nan<v_t>() : std::nextafter(e, eve::minf(eve::as<v_t>())); } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::saturated_(eve::prev));
  }
  else
  {
    auto std_prev = tts::vectorize<T>( [](auto e) { return e == eve::valmin(eve::as<v_t>()) ? e : e-1; } );
    eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::saturated_(eve::prev));
  }
}
