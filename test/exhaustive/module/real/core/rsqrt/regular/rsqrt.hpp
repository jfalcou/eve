//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on rsqrt", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_rsqrt = tts::vectorize<T>( [](auto e) { return v_t(1)/std::sqrt(e); } );

  eve::exhaustive_producer<T> p(eve::smallestposval(eve::as<v_t>()), v_t(eve::valmax(eve::as<float>())));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::rsqrt);
}
