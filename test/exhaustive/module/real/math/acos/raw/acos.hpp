//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on acos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acos = tts::vectorize<T>( [](auto e) { return std::acos(e); } );

  double th = std::is_same_v<v_t, double> ? 4096.0 : 512.0;
  eve::exhaustive_producer<T> p(-1,1);
  TTS_ULP_RANGE_CHECK(p, std_acos, eve::raw(eve::acos), th);
}
