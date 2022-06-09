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
auto cv(std::complex < T > const &sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of exp on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::exp(eve::complex<e_t>(e, f)),  cv(std::exp(c_t(e, f))), 2.0);
      TTS_ULP_EQUAL(eve::exp(eve::complex<e_t>(e, f)),  cv(std::exp(c_t(e, f))), 2.0);
    }
  }
};

EVE_TEST( "Check behavior of exp on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t =  eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_exp = [](auto x, auto y){return cv(std::exp(c_t(x, y))); };
  auto init_with_std = [std_exp](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_exp(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::exp(z_t{a0,a1}), init_with_std(a0, a1), 2);
};

EVE_TEST_TYPES( "Check behavior of log2"
        , eve::test::simd::ieee_reals
            )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using z_t = eve::as_complex_t<T>;
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto zer = eve::zero(as<T>());
  auto nan = eve::nan(as<T>());
  auto one= eve::one(as<T>());
  auto e =  eve::euler(as<T>());
  TTS_ULP_EQUAL(eve::exp(z_t{inf, zer}),   (z_t{inf, zer}), 0.5);
  TTS_ULP_EQUAL(eve::exp(z_t{minf, zer}),  (z_t{zer, zer}), 0.5);

  TTS_ULP_EQUAL(eve::exp(z_t{nan, zer}),   (z_t{nan, zer}), 0.5);
  TTS_ULP_EQUAL(eve::exp(z_t{nan, nan}),   (z_t{nan, nan}), 0.5);
  TTS_ULP_EQUAL(eve::exp(z_t{one, zer}),   (z_t{e, zer}), 0.5);
  TTS_ULP_EQUAL(eve::exp(z_t{zer, zer}),   (z_t{one, zer}), 0.5);
};
