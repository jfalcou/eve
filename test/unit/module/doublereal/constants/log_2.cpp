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

TTS_CASE_TPL( "Check log_2 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using doublereal_t   = eve::doublereal<T>;
  auto doublereallog_2 = eve::log_2(eve::as<doublereal_t>());
  auto bmlog_2 = bm::log(f128(2));
  TTS_ULP_EQUAL(doublereallog_2, tts::to_doublereal<doublereal_t>(bmlog_2), 0.5);

  auto d =eve::downward(eve::log_2)(eve::as<doublereal_t>());
  auto u = eve::upward(eve::log_2)(eve::as<doublereal_t>());
  auto n = eve::log_2 (eve::as<doublereal_t>());

  TTS_LESS_EQUAL(d, doublereallog_2);
  TTS_GREATER_EQUAL(u, doublereallog_2);
  TTS_EXPECT(eve::all(u == n || d == n));
};
