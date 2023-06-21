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


TTS_CASE_WITH ( "Check behavior of pow on wide"
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

  auto mybeta = [](auto a,  auto b){return eve::tgamma(a)*eve::tgamma(b)/eve::tgamma(a+b); };
  TTS_ULP_EQUAL(eve::beta(a, b), mybeta(a, b), 0.5);
};

TTS_CASE_TPL( "Check corner cases of log", eve::test::scalar::ieee_reals)
  <typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  c_t i(0, 1);
  c_t o(1, 0);
  TTS_ULP_EQUAL(eve::beta(i, i),      c_t(-2.376146124821733192409666, -2.63956852027813624177239618242498), 32);
  TTS_ULP_EQUAL(eve::beta(i, T(0.5)), c_t(1.0794242492709257801356755, -1.41003240566416083828875193632476), 32);
  TTS_ABSOLUTE_EQUAL(eve::beta(i, o), -i                                                                   , 32*eve::eps(eve::as<T>()));
  TTS_ULP_EQUAL(eve::beta(o, T(0.5)), c_t(2)                                                               , 32);
  TTS_ULP_EQUAL(eve::beta(i, 2*i),    c_t(-2.891319789417896828442673, -1.04053537453220827379062834820451), 36);
};
