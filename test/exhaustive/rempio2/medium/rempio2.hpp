//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rempio2.hpp>
#include <eve/function/rem_pio2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>

TTS_CASE_TPL("wide random check on rempio2", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_rempio2_n = tts::vectorize<T>( [](auto e) { auto [n, x, dx] = eve::rem_pio2(e); return n; } );
  auto std_rempio2_x = tts::vectorize<T>( [](auto e) { auto [n, x, dx] = eve::rem_pio2(e); return x; } );

  auto rempio2_n =  [](auto e) { auto [n, x, dx] = eve::medium_(eve::rempio2)(e); return n; };
  auto rempio2_x =  [](auto e) { auto [n, x, dx] = eve::medium_(eve::rempio2)(e); return x; };

  auto l = eve::detail::Rempio2_limit(eve::medium_type(), v_t());

  eve::exhaustive_producer<T> p(0, l);
  TTS_RANGE_CHECK(p, std_rempio2_n, rempio2_n);
  TTS_RANGE_CHECK(p, std_rempio2_x, rempio2_x);
}
