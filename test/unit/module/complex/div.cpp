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
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::div(a, b), a/b, 0.5);
  TTS_ULP_EQUAL( eve::pedantic(eve::div)(a, b), a/b, 10);
  {
    z_t c(1, eve::inf(eve::as(a0)));
    z_t rr(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), rr, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), 1);
    z_t rp(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rp, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), rp, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), eve::inf(eve::as(a0)));
    z_t rr(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), rr, 0.5);
  }
};
