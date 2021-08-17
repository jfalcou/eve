//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/atand.hpp>
#include <eve/function/radindeg.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on atand", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_atand = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::atan(e)); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_atand, eve::atand);
}
