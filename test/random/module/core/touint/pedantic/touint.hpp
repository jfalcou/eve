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
  using  ui_t = eve::detail::as_integer_t<T,  unsigned>;
  using v_t = eve::element_type_t<T>;
  using sui_t = eve::detail::as_integer_t<v_t,  unsigned>;
  using si_t = eve::detail::as_integer_t<v_t>;
  if constexpr(eve::floating_value<T>)
  {
    auto lmin = v_t(sui_t(0));
    auto lmax = v_t(eve::Valmax<sui_t>());
    auto std_touint = tts::vectorize<ui_t>( [](auto e) { return sui_t(e); } );
    eve::rng_producer<T> p(lmin, lmax);
    TTS_RANGE_CHECK(p, std_touint, eve::pedantic_(eve::touint));
  }
  else if constexpr(eve::signed_integral_value<T>)
  {
    auto lmin = v_t(sui_t(0));
    auto lmax = v_t(eve::Valmax<si_t>());
    auto std_touint = tts::vectorize<ui_t>( [](auto e) { return sui_t(e); } );
    eve::rng_producer<T> p(lmin, lmax);
    TTS_RANGE_CHECK(p, std_touint, eve::pedantic_(eve::touint));
  }
  else
  {
    auto lmin = v_t(sui_t(0));
    auto lmax = v_t(eve::Valmax<sui_t>());
    auto std_touint = tts::vectorize<T>( [](auto e) { return e; } );
    eve::rng_producer<T> p(lmin, lmax);
    TTS_RANGE_CHECK(p, std_touint, eve::pedantic_(eve::touint));
  }
}
