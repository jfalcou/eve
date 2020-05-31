//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_flint.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on is_flint", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t = eve::as_logical_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_flint = tts::vectorize<l_t>( [](auto e) { return (std::remainder(e, v_t(1)) == v_t(0)); } );
    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_is_flint, eve::is_flint);
  }
  else
  {
    auto std_is_flint = tts::vectorize<l_t>( [](auto e) { return true; } );
    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_is_flint, eve::is_flint);
  }
}
