//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/touint.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on touint", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<v_t>;
    auto std_touint = tts::vectorize<T>( [](auto e) { return i_t(e); } );
    eve::rng_producer<T> p(eve::Valmin<v_t>()+1, eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_touint, eve::touint);
  }
  else if constexpr(eve::integral_value<T>)
  {
    auto std_touint = tts::vectorize<T>( [](auto e) { return e; } );
    eve::rng_producer<T> p(eve::Valmin<v_t>()+1, eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_touint, eve::touint);
  }
  else
  {
    auto std_touint = tts::vectorize<T>( [](auto e) { return e; } );
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_touint, eve::touint);
  }
}
