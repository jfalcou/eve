//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>

TTS_CASE_TPL("wide random check on tan", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_tan = tts::vectorize<T>( [](auto e) { return std::tan(e); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), v_t());

  eve::exhaustive_producer<T>  p(-l, l);
  TTS_RANGE_CHECK(p, std_tan, eve::medium_(eve::tan));
}
