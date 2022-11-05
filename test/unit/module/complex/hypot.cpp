//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of hypot on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::hypot(a, b),      eve::sqrt(eve::sqr_abs(a)+eve::sqr_abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::hypot(a, a2),     eve::sqrt(eve::sqr_abs(a)+eve::sqr_abs(a2)), 0.5);
  TTS_ULP_EQUAL( eve::hypot(a0, b),     eve::sqrt(eve::sqr_abs(a0)+eve::sqr_abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::hypot(a, T(1.0)), eve::sqrt(eve::inc(eve::sqr_abs(a))), 0.5);
};
