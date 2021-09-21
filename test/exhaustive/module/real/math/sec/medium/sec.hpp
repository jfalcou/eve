//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sec", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_sec = tts::vectorize<T>( [](auto e) { return 1/std::cos(double(e)); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<v_t>());

  eve::exhaustive_producer<T>  p(-l, l);
  TTS_RANGE_CHECK(p, std_sec, eve::medium(eve::sec));
}
