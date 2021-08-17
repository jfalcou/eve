//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on log1p", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_log1p = tts::vectorize<T>( [](auto e) { return std::log1p(e); } );

  eve::exhaustive_producer<T> p(v_t(-1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_log1p, eve::log1p);
}
