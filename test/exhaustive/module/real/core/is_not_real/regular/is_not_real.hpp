//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_not_real.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_not_real", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using l_t =  eve::as_logical_t<T>;
  auto std_is_not_real = tts::vectorize<l_t>( [](auto ) { return false; } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_is_not_real, eve::is_not_real);
}
