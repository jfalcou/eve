//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on gamma", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_erfcx = tts::vectorize<T>([](auto e) { return eve::erfcx(double(e)); });

  eve::exhaustive_producer<T> p(v_t(-7), v_t(-1)); //eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_erfcx, eve::erfcx);
}
