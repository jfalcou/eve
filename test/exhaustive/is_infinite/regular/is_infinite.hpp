//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_infinite.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on is_infinite", EVE_TYPE)
{
  using l_t = eve::as_logical_t<T>;
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    auto std_is_infinite = tts::vectorize<l_t>( [](auto e) { return std::isinf(e); } );

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_is_infinite, eve::is_infinite);
  }
  else
  {
    auto std_is_infinite = tts::vectorize<l_t>( [](auto e) { return false; } );

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_is_infinite, eve::is_infinite);
  }
}
