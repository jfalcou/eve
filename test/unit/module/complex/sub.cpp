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

TTS_CASE_WITH( "Check behavior of average on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2 , T const& a3, T const& a4 , T const& a5 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto c = z_t(a4, a5);
  TTS_ULP_EQUAL( eve::sub(a, b), a-b, 0.5);
  TTS_ULP_EQUAL( eve::sub(a, b, c), a-b-c, 0.5);
  TTS_ULP_EQUAL( eve::pedantic(eve::sub)(a, b), a-b, 0.5);
  {
    z_t c(1, eve::inf(eve::as(a0)));
    z_t a(2.0, 3.0);
    z_t rr(1.0, eve::minf(eve::as(a0)));
    z_t ac = a-c;
    z_t  d = eve::pedantic(eve::sub)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::sub(a, c), rr, 0.5);
    TTS_ULP_EQUAL( ac, rr, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), a0);
    z_t rr(eve::minf(eve::as(a0)), -a0);
    z_t a(1, 0);
    z_t  d = eve::pedantic(eve::sub)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::sub(a, c), rr, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), 1.5);
    z_t rr(eve::nan(eve::as(a0)), 0.0);
    z_t a(eve::inf(eve::as(a0)), 1.5);
    z_t  d = eve::pedantic(eve::sub)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::sub(a, c), rr, 0.5);
  }
};
