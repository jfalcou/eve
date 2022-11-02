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
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2 , T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::add(a, b), a+b, 0.5);
 TTS_ULP_EQUAL( eve::pedantic(eve::add)(a, b), a+b, 0.5);
  {
    z_t c(1, eve::inf(eve::as(a0)));
    z_t a(2.0, 3.0);
    z_t rr(3.0, eve::inf(eve::as(a0)));
    z_t ac = a+c;
    z_t  d = eve::pedantic(eve::add)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::add(a, c), rr, 0.5);
    TTS_ULP_EQUAL( ac, rr, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), a0);
    z_t rr(eve::inf(eve::as(a0)), a0);
    z_t a(1, 0);
    z_t  d = eve::pedantic(eve::add)(a, c);
    TTS_ULP_EQUAL( d, c, 0.5);
    TTS_ULP_EQUAL( eve::add(a, c), rr, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), 1.5);
    z_t rr(eve::inf(eve::as(a0)), 3.0);
    z_t a(eve::inf(eve::as(a0)), 1.5);
    z_t  d = eve::pedantic(eve::add)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::add(a, c), rr, 0.5);
 }
};
