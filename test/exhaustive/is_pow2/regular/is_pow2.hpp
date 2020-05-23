//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/popcount.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on is_pow2", EVE_TYPE)
{
  using l_t = eve::as_logical_t<T>;
  using v_t = eve::element_type_t<T>;

  auto std_is_pow2 = tts::vectorize<l_t>( [](auto e) { return ((e > 0) && (eve::popcount(e) == 1u));} );

  eve::exhaustive_producer<T> p(eve::Zero<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_is_pow2, eve::is_pow2);
}
