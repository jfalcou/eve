//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on inc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_inc = tts::vectorize<T>( [](auto e) { return e == Valmax<v_t>() ? Valmin<v_t>() : e+1; } );
    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_inc, eve::inc);
  }
}
