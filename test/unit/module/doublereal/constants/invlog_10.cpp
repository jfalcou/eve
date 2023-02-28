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

TTS_CASE_TPL( "Check invlog_10 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using doublereal_t   = eve::doublereal<T>;
  auto doublerealinvlog_10 = eve::invlog_10(eve::as<doublereal_t>());
  auto bminvlog_10 = f128(1)/bm::log(f128(10));
  TTS_ULP_EQUAL(doublerealinvlog_10, tts::to_doublereal<doublereal_t>(bminvlog_10), 0.5);

  auto d =eve::downward(eve::invlog_10)(eve::as<doublereal_t>());
  auto u = eve::upward(eve::invlog_10)(eve::as<doublereal_t>());
  auto n = eve::invlog_10 (eve::as<doublereal_t>());

  TTS_LESS_EQUAL(d, doublerealinvlog_10);
  TTS_GREATER_EQUAL(u, doublerealinvlog_10);
  TTS_EXPECT(eve::all(u == n || d == n));
};
