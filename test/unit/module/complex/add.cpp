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
  using e_t = eve::element_type_t<T>;
  using c_t = eve::as_complex_t<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto c = z_t(a4, a5);
  auto ii= z_t(0, 1);
  TTS_ULP_EQUAL( eve::add(a, b), a+b, 0.5);
  TTS_ULP_EQUAL( eve::add(a, b, c), a+b+c, 0.5);
  TTS_ULP_EQUAL( eve::pedantic(eve::add)(a, b), a+b, 0.5);
  TTS_ULP_EQUAL( eve::add(a, eve::i(eve::as<T>{})), eve::add(a,ii), 0.5);
  TTS_ULP_EQUAL( eve::add(eve::i(eve::as<T>{}), a), eve::add(a,ii), 0.5);
  TTS_ULP_EQUAL( eve::add(eve::i(eve::as<e_t>{}), a), eve::add(a,ii), 0.5);
  TTS_ULP_EQUAL( eve::add(a, c_t(0, 1))           , eve::add(a,ii), 0.5);
//  TTS_ULP_EQUAL( eve::add(a, T(0))                , a, 0.5);
//  TTS_ULP_EQUAL( eve::add(a, e_t(0))              , a, 0.5);
//  TTS_ULP_EQUAL( eve::add(eve::i(eve::as<e_t>{}), T(1)), z_t(1, 1), 0.5);
//  TTS_ULP_EQUAL( eve::add(a, 1.0), eve::inc(a), 0.5);
//  TTS_ULP_EQUAL( eve::add(a, 1.0), a+1.0,  0.5);
//  c_t ca(0, 1);
//  TTS_ULP_EQUAL( eve::add(ca, 1.0), ca+1.0,  0.5);

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
