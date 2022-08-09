//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
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

TTS_CASE_WITH( "Check behavior of asinh on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(1, 10)
                             , tts::randoms(1, 10))
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

TTS_CASE_WITH( "Check behavior of asinh on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1, 5)
                             , tts::randoms(1, 5))
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

TTS_CASE_TPL( "Check corner cases of asinh", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto pio_2 = eve::pio_2(as<T>());
  auto pio_4 = eve::pio_4(as<T>());
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
    TTS_IEEE_EQUAL(asinh(inputs[i]), results[i]);
    TTS_IEEE_EQUAL(asinh(-inputs[i]), -asinh(inputs[i]));
    TTS_IEEE_EQUAL(asinh(conj(inputs[i])), conj(asinh(inputs[i])));
  }
};
