//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
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
