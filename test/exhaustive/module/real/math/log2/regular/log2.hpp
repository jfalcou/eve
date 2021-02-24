//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log2.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on log2", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_log2 = tts::vectorize<T>( [](auto e) { return std::log2(e); } );

  eve::exhaustive_producer<T> p(v_t(0), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_log2, eve::log2);
}
