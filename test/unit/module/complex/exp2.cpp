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

EVE_TEST( "Check behavior of exp2 on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using eve::as;
  auto std_exp2 =  [](auto x){return std::exp(x*eve::log_2(as<e_t>())); };
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::exp2(eve::complex<e_t>(e, f)),  cv(std_exp2(c_t(e, f))), 2.5);
      TTS_ULP_EQUAL(eve::exp2(eve::complex<e_t>(e, f)),  cv(std_exp2(c_t(e, f))), 2.5);
    }
  }
};

EVE_TEST( "Check behavior of exp2 on wide"
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
  auto std_exp2 = [](auto x, auto y){return cv(std::exp(c_t(x, y)*eve::log_2(eve::as<e_t>()))); };
  auto init_with_std = [std_exp2](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_exp2(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::exp2(z_t{a0,a1}), init_with_std(a0, a1), 2);
};
