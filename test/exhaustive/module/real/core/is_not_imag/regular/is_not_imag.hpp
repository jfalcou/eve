//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_not_imag", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t =  eve::as_logical_t<T>;
  auto std_is_not_imag = tts::vectorize<l_t>( [](auto e) { return e!= v_t(0); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_is_not_imag, eve::is_not_imag);
}
