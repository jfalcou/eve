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

TTS_CASE_WITH ( "Check behavior of pow1p on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
//  auto ulp = 100.0;
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using ce_t = eve::complex<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);

  auto init_with_std = [=](auto i, auto)
  {
    return cv(std::pow( c_t(eve::inc(a0.get(i)), a1.get(i)), c_t(a2.get(i), a3.get(i))));
  };
  auto init_with_std1 = [=](auto i, auto)
  {
    return cv(std::pow( c_t(eve::inc(eve::abs(a0.get(i))), 0), c_t(a2.get(i), a3.get(i))));
  };
  auto init_with_std2 = [=](auto i, auto)
  {
    return cv(std::pow( c_t(eve::inc(-eve::abs(a0.get(i))), 0), c_t(a2.get(i), a3.get(i))));
  };
  auto init_with_std3 = [=](auto i, auto)
  {
    c_t x(eve::inc(a2.get(i)), a3.get(i));
    c_t y(eve::abs(a0.get(i)), 0);
    return cv(std::pow(x, y));
  };

  TTS_RELATIVE_EQUAL( eve::pow1p(a, b) , z_t{init_with_std}, 0.5);
  auto ap1 = eve::inc(a);
  TTS_ULP_EQUAL( eve::pow1p(a, 2u), eve::sqr(ap1), 300);
  TTS_ULP_EQUAL( eve::pow1p(a, 3u), eve::sqr(ap1)*ap1,  300);
  TTS_ULP_EQUAL( eve::pow1p(eve::abs(a0), b)   , z_t{init_with_std1}, 300);
  TTS_RELATIVE_EQUAL( eve::pow1p(-eve::abs(a0), b)   , z_t{init_with_std2}, 0.5);
  TTS_RELATIVE_EQUAL( eve::pow1p(b, eve::abs(a0))   ,  z_t{init_with_std3}, 0.5);
  TTS_ULP_EQUAL( eve::pow1p(a, 3u)   , eve::pow1p(a, e_t(3)),  10);
  TTS_ULP_EQUAL( eve::pow1p(a, 2u)   , eve::pow1p(a, e_t(2)),  10);
  TTS_ULP_EQUAL( eve::pow1p(a, -2)   , eve::pow1p(a, e_t(-2)),  10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(0, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(1, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(1, 3), ce_t(0, 0)), ce_t(1, 0), 10);

  using eve::as;
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_ULP_EQUAL( eve::pow1p(ce_t(inf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(minf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(nan, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(nan, 1), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow1p(ce_t(-1, 0),  ce_t(0, 0)), ce_t(1, 0), 10);
};
