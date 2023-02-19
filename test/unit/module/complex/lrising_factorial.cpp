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

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of lrising_factorial on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
   using z_t = eve::as_complex_t<T>;
   auto a = z_t(a0, a1);
   auto b = z_t(a2, a3);

   auto lrf =  [](auto a,  auto b){return eve::log(eve::tgamma(a+b)/eve::tgamma(a)); };
   TTS_ULP_EQUAL( eve::lrising_factorial(a, b) , lrf(a, b), 64.0);
   TTS_ULP_EQUAL( eve::lrising_factorial(a, 0.0) , eve::zero(eve::as(a)), 0.5);
   TTS_ULP_EQUAL( eve::lrising_factorial(a, 1.0), eve::log(a), 360);
   TTS_ULP_EQUAL( eve::lrising_factorial(a, 2.0), eve::log(eve::fma(a, a, a)), 360);

   using eve::as;
   using e_t = T;
   auto inf = eve::inf(as<e_t>());
   auto minf = eve::minf(as<e_t>());
   auto nan = eve::nan(as<e_t>());

   TTS_ULP_EQUAL( eve::lrising_factorial(z_t(inf, 0), z_t(0, 0)), z_t(0, 0), 10);
   TTS_ULP_EQUAL( eve::lrising_factorial(z_t(minf, 0), z_t(0, 0)), z_t(0, 0), 10);
   TTS_ULP_EQUAL( eve::lrising_factorial(z_t(nan, 0), z_t(0, 0)), z_t(0, 0), 10);
   TTS_ULP_EQUAL( eve::lrising_factorial(z_t(nan, 1), z_t(0, 0)), z_t(0, 0), 10);
   TTS_ULP_EQUAL( eve::lrising_factorial(z_t(0, 0),  z_t(0, 0)), z_t(0, 0), 10);
   z_t i(0, 1);
   z_t o(1, 0);
   TTS_ULP_EQUAL(eve::lrising_factorial(i, i),  z_t(-1.918302767689018311762010, +0.4312866367773215092712391), 10);
   TTS_ULP_EQUAL(eve::lrising_factorial(i, T(0.5)), z_t(-0.0018674449025165763, +0.9174289229198607075556282), 2000);
   TTS_ULP_EQUAL(eve::lrising_factorial(o, T(0.5)), z_t(-0.120782237635245222345518445781647212251852727902599468363868473), 2032);
   TTS_ULP_EQUAL(eve::lrising_factorial(i, 2*i),   z_t(-3.69183338895600954408, +1.3549910915361463982113221), 100);


};
