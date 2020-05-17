//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cos", EVE_TYPE)
{
//  using v_t = eve::element_type_t<T>;
  auto std_cos = tts::vectorize<T>( [](auto e) { return std::cos(double(e)); } );

  auto l = 1.76858e+15f; //eve::detail::Rempio2_limit(eve::medium_type(), as<v_t>());
  eve::exhaustive_producer<T> p(-l, l);
  TTS_ULP_RANGE_CHECK(p, std_cos, eve::medium_(eve::cos), 0.5);
}
