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
   TTS_ULP_EQUAL( eve::lrising_factorial(a, b) , lrf(a, b), 0.5);
   TTS_RELATIVE_EQUAL( eve::lrising_factorial(a, 0.0) , eve::zero(eve::as(a)), 0.0005);
   TTS_ULP_EQUAL( eve::lrising_factorial(a, 1.0), eve::log(a), 200);
   TTS_ULP_EQUAL( eve::lrising_factorial(a, 2.0), eve::log(eve::fma(a, a, a)), 200);

};
