//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exponent", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;

  auto internal_f = [](auto e){  int exp; std::frexp(e, &exp); return i_t(exp); };
  using vi_t = eve::as_integer_t<T>;

  auto std_exponent = tts::vectorize<vi_t>( [ internal_f ](auto e) { return internal_f(e); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_exponent, eve::exponent);
}
