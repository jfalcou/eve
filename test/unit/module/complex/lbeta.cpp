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
#include <eve/module/core.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of lbeta on wide"
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

  auto mylbeta = [](auto a,  auto b){return eve::log(eve::beta(a, b)); };
  TTS_ULP_EQUAL(eve::lbeta(a, b), mylbeta(a, b), 0.5);


};

TTS_CASE_TPL( "Check corner cases of log", eve::test::scalar::ieee_reals)
  <typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  c_t i(0, 1);
  c_t o(1, 0);
  TTS_ULP_EQUAL(eve::lbeta(i, i),      c_t(1.2673795683871619728767940, -2.30372328403975132639009246361848), 32);
  TTS_ULP_EQUAL(eve::lbeta(i, T(0.5)), c_t(0.574232387827216663459561, -0.917428922919860707555628220702128), 32);
  TTS_ABSOLUTE_EQUAL(eve::lbeta(i, o), -i*eve::pio_2(eve::as<T>())                                          , 32*eve::eps(eve::as<T>()));
  TTS_ULP_EQUAL(eve::lbeta(o, T(0.5)), c_t(eve::log(T(2)))                                                  , 32);
  TTS_ULP_EQUAL(eve::lbeta(i, 2*i),    c_t(1.122607421965134893435985, -2.796141102021254706058936433559202), 32);
};
