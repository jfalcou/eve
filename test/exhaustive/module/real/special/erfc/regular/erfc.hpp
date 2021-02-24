//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/function/erfc.hpp>
#include <tts/tests/range.hpp>
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
