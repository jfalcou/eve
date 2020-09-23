//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/function/iota.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on pow_abs", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_pow_abs = tts::vectorize<T>( [](auto e) { return eve::pow_abs(e, v_t(10.51)); } );
  auto  my_pow_abs =  [](auto e) {  return (eve::pow_abs)(e,  v_t(10.51)); };
  eve::rng_producer<T> p(v_t(0.05), v_t(100.0));
  TTS_ULP_RANGE_CHECK(p, std_pow_abs, my_pow_abs, 8);

  auto std_pow_abs1 = tts::vectorize<T>( [](auto e) { return eve::pow_abs(v_t(0.51), e); } );
  auto  my_pow_abs1 =  [](auto e) {  return (eve::pow_abs)(v_t(0.51), e); };

  eve::rng_producer<T> p1(v_t(0.05), v_t(10.5));
  TTS_ULP_RANGE_CHECK(p1, std_pow_abs1, my_pow_abs1, 8);

}
