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

EVE_TEST( "Check behavior of pow on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto ulp = (spy::stdlib_type() == spy::libcpp_) ? 300.0 : 300.0;
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using c_t = std::complex<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto std_pow = [](auto x, auto y, auto z, auto t){return std::pow(c_t(x, y), c_t(z, t)); };
  auto init_with_std = [std_pow](auto a0,  auto a1,  auto a2,  auto a3){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_pow(a0.get(i), a1.get(i), a2.get(i), a3.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL( eve::pow(a, b)   , init_with_std(a0, a1, a2, a3), ulp);
  TTS_ULP_EQUAL( eve::pow(a, 2u)   , eve::sqr(a), ulp);
  TTS_ULP_EQUAL( eve::pow(a, 3u)   , eve::sqr(a)*a,  ulp);
  TTS_ULP_EQUAL( eve::pow(eve::abs(a0), b)   , init_with_std(eve::abs(a0), eve::zero(eve::as(a0)), a2, a3), ulp);
  TTS_ULP_EQUAL( eve::pow(-eve::abs(a0), b)   , init_with_std(-eve::abs(a0), eve::zero(eve::as(a0)), a2, a3), ulp);
  TTS_ULP_EQUAL( eve::pow(b, eve::abs(a0))   , init_with_std(a2, a3, eve::abs(a0), eve::zero(eve::as(a0))), ulp);
  TTS_ULP_EQUAL( eve::pow(a, 3u)   , eve::pow(a, e_t(3)),  10);
  TTS_ULP_EQUAL( eve::pow(a, 2u)   , eve::pow(a, e_t(2)),  10);
  TTS_ULP_EQUAL( eve::pow(a, -2)   , eve::pow(a, e_t(-2)),  10);
  TTS_ULP_EQUAL( eve::pow(ce_t(0, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow(ce_t(1, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow(ce_t(1, 3), ce_t(0, 0)), ce_t(1, 0), 10);

  using eve::as;
  //   auto zer = eve::zero(as<e_t>());
  //   auto mzer = eve::mzero(as<e_t>());
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_ULP_EQUAL( eve::pow(ce_t(inf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow(ce_t(minf, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow(ce_t(nan, 0), ce_t(0, 0)), ce_t(1, 0), 10);
  TTS_ULP_EQUAL( eve::pow(ce_t(nan, 1), ce_t(0, 0)), ce_t(1, 0), 10);

};

