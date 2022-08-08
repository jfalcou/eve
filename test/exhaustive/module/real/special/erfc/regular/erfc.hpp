//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <tts/tests/range.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/core.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on erfc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_erfc = tts::vectorize<T>([](auto e) { return std::erfc(double(e)); });

  eve::exhaustive_producer<T> p(eve::Minlog<v_t>(), eve::Maxlog<v_t>());
  TTS_RANGE_CHECK(p, std_erfc, eve::erfc);
}
