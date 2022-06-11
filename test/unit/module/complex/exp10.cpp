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

template < typename T >
auto sc(eve::complex < T > const &ec)
{
  return std::complex<T>(eve::real(ec), eve::imag(ec));
}

EVE_TEST( "Check behavior of exp10 on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using eve::as;
  auto std_exp10 =  [](auto x){return std::exp(x*eve::log_10(as<e_t>())); };
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::exp10(eve::complex<e_t>(e, f)),  cv(std_exp10(c_t(e, f))), 2.5);
      TTS_ULP_EQUAL(eve::exp10(eve::complex<e_t>(e, f)),  cv(std_exp10(c_t(e, f))), 2.5);
    }
  }
};

EVE_TEST( "Check behavior of exp10 on wide"
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
  auto std_exp10 = [](auto x, auto y){return cv(std::exp(c_t(x, y)*eve::log_10(eve::as<e_t>()))); };
  auto init_with_std = [std_exp10](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_exp10(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::exp10(z_t{a0,a1}), init_with_std(a0, a1), 3);
};

EVE_TEST_TYPES( "Check corner cases of exp10", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<e_t>());
  auto inf = eve::inf(as<e_t>());
  auto nan = eve::nan(as<e_t>());
  auto one = eve::one(as<e_t>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(zer,inf), //1
      c_t(zer,nan), //2
      c_t(one,inf), //3
      c_t(one,nan), //4
      c_t(inf,zer), //5
      c_t(inf,one), //6
      c_t(inf,inf), //7
      c_t(inf,nan), //8
      c_t(nan,zer), //9
      c_t(nan,one), //10
      c_t(nan,nan), //11
    };

  using eve::conj;
  using eve::exp10;
  auto test_exp10 = [](auto z){ return cv(std::exp(eve::log_10(eve::as<e_t>())*sc(z))); };
  for(int i=0; i < N; ++i)
  {
     std::cout << "i " << i << " -> " << inputs[i] << std::endl;
     TTS_IEEE_EQUAL(exp10(inputs[i]), test_exp10(inputs[i]));
    TTS_IEEE_EQUAL(exp10(conj(inputs[i])), conj(exp10(inputs[i])));
  }
};
