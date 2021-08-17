//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cos", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(double(e)); } );

  auto l = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<v_t>());
  eve::exhaustive_producer<T> p(-l, l);
  TTS_ULP_RANGE_CHECK(p, std_cos, eve::medium(eve::cos), 0.5);
}
