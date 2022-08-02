//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
  TTS_ULP_EQUAL( eve::mul(a, b), a*b, 0.5);
  TTS_ULP_EQUAL( eve::pedantic(eve::mul)(a, b), a*b, 0.5);
  if (eve::cardinal_v<T> == 1)
  {
    {
      z_t c(a0, eve::inf(eve::as(a0)));
      z_t rr(eve::inf(eve::as(a0)), eve::minf(eve::as(a0)));
      z_t  d = eve::pedantic(eve::mul)(a, c);
      TTS_ULP_EQUAL( d, rr, 0.5);
      TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
    }
    {
      z_t c(eve::inf(eve::as(a0)), a0);
      z_t rp(c);
      z_t rr(eve::inf(eve::as(a0)), eve::nan(eve::as(a0)));
      z_t  d = eve::pedantic(eve::mul)(a, c);
      TTS_ULP_EQUAL( d, rp, 0.5);
      TTS_ULP_EQUAL( eve::mul(a, c), c, 0.5);
    }
    {
      z_t c(eve::inf(eve::as(a0)), a0);
      z_t rr(eve::inf(eve::as(a0)), eve::minf(eve::as(a0)));
      z_t  d = eve::pedantic(eve::mul)(a, c);
      TTS_ULP_EQUAL( d, rr, 0.5);
      TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
    }
  }
};
