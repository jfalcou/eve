//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <string>

TTS_CASE_TPL( "Check euler value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using doublereal_t   = eve::doublereal<T>;
  auto doublerealeuler = eve::euler(eve::as<doublereal_t>());
  auto bmeuler = bm::exp(f128(1));
  TTS_ULP_EQUAL(doublerealeuler, tts::to_doublereal<doublereal_t>(bmeuler), 0.5);

  auto d =eve::downward(eve::euler)(eve::as<doublereal_t>());
  auto u = eve::upward(eve::euler)(eve::as<doublereal_t>());
  auto n = eve::euler (eve::as<doublereal_t>());

  TTS_LESS_EQUAL(d, doublerealeuler);
  TTS_GREATER_EQUAL(u, doublerealeuler);
  TTS_EXPECT(eve::all(u == n || d == n));
};
