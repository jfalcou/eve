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


TTS_CASE_WITH ( "Check behavior of rising_factorial on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
//  auto ulp = 100.0;
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);

  auto rf =  [](auto x,  auto a){return eve::tgamma(a+x)/eve::tgamma(x); };

  TTS_RELATIVE_EQUAL( eve::rising_factorial(a, b) , rf(a, b), 0.001);
  TTS_ULP_EQUAL( eve::rising_factorial(a, ce_t(2, 0)), a*(a+1), 13000);
  TTS_ULP_EQUAL( eve::rising_factorial(a, ce_t(3, 0)), a*(a+1)*(a+2),  300);
  TTS_ULP_EQUAL( eve::rising_factorial(eve::abs(a0), b)   , rf(eve::abs(a0), b), 300);
  TTS_ULP_EQUAL( eve::rising_factorial(-eve::abs(a0), b)   , rf(-eve::abs(a0), b), 300);
  TTS_RELATIVE_EQUAL( eve::rising_factorial(b, eve::abs(a0))   ,  rf(b, eve::abs(a0)), 0.5);
  TTS_ULP_EQUAL( eve::rising_factorial(a, 3u)   , eve::rising_factorial(a, e_t(3)),  10);
  TTS_ULP_EQUAL( eve::rising_factorial(a, 2u)   , eve::rising_factorial(a, e_t(2)),  10);
  TTS_ULP_EQUAL( eve::rising_factorial(a, -2)   , eve::rising_factorial(a, e_t(-2)),  10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(0, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(1, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(1, 3), ce_t(0, 0)), ce_t(1, 0), 10);

  using eve::as;
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(inf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(minf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(nan, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(nan, 1), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::rising_factorial(ce_t(0, 0),  ce_t(0, 0)), ce_t(1, 0), 10);
  z_t i(0, 1);
  z_t o(1, 0);
  TTS_ULP_EQUAL(eve::rising_factorial(i, i),      z_t(0.133408195318916183621, +0.06139167700318597540461), 32);
  TTS_ULP_EQUAL(eve::rising_factorial(i, T(0.5)), z_t(0.60672961239287904055952, +0.7925599369551407652246), 32);
  TTS_ABSOLUTE_EQUAL(eve::rising_factorial(i, o), i, 32*eve::eps(eve::as<e_t>()));
  TTS_ULP_EQUAL(eve::rising_factorial(o, T(0.5)), z_t(0.88622692545275801364908), 32);
  TTS_ULP_EQUAL(eve::rising_factorial(i, 2*i),    z_t(0.00533756125402432030171473451274, +0.024348078097112309674412896870731), 100);
};
