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

TTS_CASE_TPL( "Check inv_pi value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using doublereal_t   = eve::doublereal<T>;
  auto doublerealinv_pi = eve::inv_pi(eve::as<doublereal_t>());
  auto bminv_pi = 1/(bm::atan(f128(1))*4);
  TTS_ULP_EQUAL(doublerealinv_pi, tts::to_doublereal<doublereal_t>(bminv_pi), 0.5);

  auto d =eve::downward(eve::inv_pi)(eve::as<doublereal_t>());
  auto u = eve::upward(eve::inv_pi)(eve::as<doublereal_t>());
  auto n = eve::inv_pi (eve::as<doublereal_t>());

  TTS_LESS_EQUAL(d, doublerealinv_pi);
  TTS_GREATER_EQUAL(u, doublerealinv_pi);
  TTS_EXPECT(eve::all(u == n || d == n));
};
