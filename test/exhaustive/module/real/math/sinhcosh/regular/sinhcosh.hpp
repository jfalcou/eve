//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sinhcosh", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sin = tts::vectorize<T>( [](auto e) { return std::sinh(double(e)); } );
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cosh(double(e)); } );
  auto sinhcosh_s =  [](auto e) { auto [s, c] = eve::sinhcosh(e); return s; };
  auto sinhcosh_c =  [](auto e) { auto [s, c] = eve::sinhcosh(e); return c; };

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_sin, sinhcosh_s);
  TTS_RANGE_CHECK(p, std_cos, sinhcosh_c);
}
