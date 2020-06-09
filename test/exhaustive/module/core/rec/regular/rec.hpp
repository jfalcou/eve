//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on rec", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::integral_value<T>)
  {
    auto std_rec = tts::vectorize<T>( [](auto e) { return e ? v_t(1)/e : eve::Valmax<v_t>(); } );

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
  else
  {
    auto std_rec = tts::vectorize<T>( [](auto e) { return v_t(1)/e; } );

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
}
