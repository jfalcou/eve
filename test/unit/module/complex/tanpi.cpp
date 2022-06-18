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

EVE_TEST( "Check behavior of tanpi on scalar"
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
      TTS_ULP_EQUAL(eve::tanpi(eve::complex<e_t>(e, f)),  cv(std::tan(eve::pi(eve::as<e_t>())*c_t(e, f))), 100.0);
    }
  }
};

EVE_TEST( "Check behavior of tanpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return std::tan(eve::pi(eve::as<e_t>())*c_t(x, y)); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::tanpi(z_t{a0,a1}), init_with_std(a0, a1), 100);
};


EVE_TEST_TYPES( "Check corner cases of tanpi", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 9;
  auto zer = eve::zero(as<e_t>());
  auto inf = eve::inf(as<e_t>());
  auto nan = eve::nan(as<e_t>());
  auto one = eve::one(as<e_t>());
//  auto mze = eve::mzero(as<e_t>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(one,inf), //1
      c_t(one,nan), //2
      c_t(inf,one), //3
      c_t(inf,inf), //4
      c_t(inf,nan), //5
      c_t(nan,zer), //6
      c_t(nan,one), //7
      c_t(nan,nan)  //8
    };

  auto test_tangentpi = [](auto x){return eve::tan(eve::pi(eve::as<e_t>{})*x); };
  std::array<c_t, N> results =
    {
      test_tangentpi(c_t(zer,zer)), //0
      test_tangentpi(c_t(one,inf)), //1
      test_tangentpi(c_t(one,nan)), //2
      test_tangentpi(c_t(inf,one)), //3
      c_t(zer,one), //4
      test_tangentpi(c_t(inf,nan)), //5
      c_t(nan,zer), //6
      test_tangentpi(c_t(nan,one)), //7
      test_tangentpi(c_t(nan,nan))  //8
    };


  using eve::conj;
  auto tangentpi = eve::tanpi;
  for(int i=0; i < N; ++i)
  {
    std::cout << "i " << i << " -> " << inputs[i] << std::endl;
    TTS_IEEE_EQUAL(tangentpi(inputs[i]), results[i]);
    TTS_IEEE_EQUAL(tangentpi(-inputs[i]), -results[i]);
    TTS_IEEE_EQUAL(tangentpi(conj(inputs[i])), conj(results[i]));
  }
};
