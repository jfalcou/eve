//==================================================================================================
/*
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/fls.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on fls", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_fls = tts::vectorize<T>( [](auto e) { return e & (~e+1); } );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_fls, eve::fls);
}
