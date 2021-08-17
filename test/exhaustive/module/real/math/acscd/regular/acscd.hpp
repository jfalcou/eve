//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/acscd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/rec.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE_TPL("wide random check on acscd", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_acscd = tts::vectorize<T>( [](auto e) { return eve::radindeg(std::asin(eve::rec(e))); } );

  eve::exhaustive_producer<T> p1(eve::valmin(eve::as<v_t>()), v_t(-1));
  TTS_RANGE_CHECK(p1, std_acscd, eve::acscd);

  eve::exhaustive_producer<T> p2(v_t(1), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p2, std_acscd, eve::acscd);
}
