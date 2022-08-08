//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on mantissa", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto internal_f = [](auto e){  int exp; return std::frexp(e, &exp);  };
  auto std_mantissa = tts::vectorize<T>( [ internal_f ](auto e) { return internal_f(e); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_mantissa, eve::mantissa);
}
