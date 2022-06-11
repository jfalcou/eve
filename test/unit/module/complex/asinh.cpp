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
#include <boost/math/complex/asinh.hpp>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of asinh on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 300.0 : 3.5;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::asinh(eve::complex<e_t>(e, f)),  cv(boost::math::asinh(c_t(e, f))), ulp);
    }
  }
};

EVE_TEST( "Check behavior of asinh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-5, 5)
                             , eve::test::randoms(-5, 5))
        )
  <typename T>(T const& a0, T const&  a1)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 300.0 : 2.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_asinh = [](auto x, auto y){return cv(boost::math::asinh(c_t(x, y))); };
  auto init_with_std = [std_asinh](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_asinh(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::asinh(z_t{a0,a1}), init_with_std(a0, a1), ulp);
};

EVE_TEST_TYPES( "Check corner cases of asinh", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<e_t>());
  auto mzer = eve::mzero(as<e_t>());
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());
  auto one = eve::one(as<e_t>());
  auto pio_2 = eve::pio_2(as<e_t>());
  auto pio_4 = eve::pio_4(as<e_t>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(one,nan), //3
      c_t(inf,one), //4
      c_t(inf,inf), //5
      c_t(inf,nan), //6
      c_t(inf,one), //7
      c_t(nan,zer),//8
      c_t(nan, one), //9
      c_t(nan,inf), //10
      c_t(nan,nan),  //11
    };

  std::array<c_t, N> results =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(inf, pio_2), //2
      c_t(nan,nan),//3
      c_t(inf,zer), //4
      c_t(inf,pio_4), //5
      c_t(inf,nan), //6
      c_t(inf,zer), //7
      c_t(nan,zer),//8
      c_t(nan, nan), //9
      c_t(minf, nan), //10
      c_t(nan,nan),  //11
    };

  using eve::conj;
  using eve::asinh;
  for(int i=0; i < N; ++i)
  {
    std::cout << "i " << i << " -> " << inputs[i] << std::endl;
    TTS_IEEE_EQUAL(asinh(inputs[i]), results[i]);
    TTS_IEEE_EQUAL(asinh(-inputs[i]), -asinh(inputs[i]));
    TTS_IEEE_EQUAL(asinh(conj(inputs[i])), conj(asinh(inputs[i])));
  }
};
