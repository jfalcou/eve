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
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of pow on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);

  auto init_with_std = [=](auto i, auto)
  {
    return cv(std::pow( c_t(a0.get(i), a1.get(i)), c_t(a2.get(i), a3.get(i))));
  };

  TTS_ULP_EQUAL( eve::pow(a, b) , z_t{init_with_std}, 300);
  TTS_ULP_EQUAL( eve::pow(a, 2u), eve::sqr(a), 300);
  TTS_ULP_EQUAL( eve::pow(a, 3u), eve::sqr(a)*a,  300);
  // TTS_ULP_EQUAL( eve::pow(eve::abs(a0), b)   , init_with_std(eve::abs(a0), eve::zero(eve::as(a0)), a2, a3), ulp);
  // TTS_ULP_EQUAL( eve::pow(-eve::abs(a0), b)   , init_with_std(-eve::abs(a0), eve::zero(eve::as(a0)), a2, a3), ulp);
  // TTS_ULP_EQUAL( eve::pow(b, eve::abs(a0))   , init_with_std(a2, a3, eve::abs(a0), eve::zero(eve::as(a0))), ulp);
  // TTS_ULP_EQUAL( eve::pow(a, 3u)   , eve::pow(a, e_t(3)),  10);
  // TTS_ULP_EQUAL( eve::pow(a, 2u)   , eve::pow(a, e_t(2)),  10);
  // TTS_ULP_EQUAL( eve::pow(a, -2)   , eve::pow(a, e_t(-2)),  10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(0, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(1, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(1, 3), ce_t(0, 0)), ce_t(1, 0), 10);

  // using eve::as;
  // auto inf = eve::inf(as<e_t>());
  // auto minf = eve::minf(as<e_t>());
  // auto nan = eve::nan(as<e_t>());

  // TTS_ULP_EQUAL( eve::pow(ce_t(inf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(minf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(nan, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  // TTS_ULP_EQUAL( eve::pow(ce_t(nan, 1), ce_t(0, 0)), ce_t(1, 0), 10);
};

