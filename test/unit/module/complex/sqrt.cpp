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
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of sqrt on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(1, 10)
                             , tts::randoms(1, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 50.0;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::sqrt(eve::complex<e_t>(e, f)),  cv(std::sqrt(c_t(e, f))), ulp);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sqrt on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1, 10)
                             , tts::randoms(1, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 50.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t =  eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_sqrt = [](auto x, auto y){return cv(std::sqrt(c_t(x, y))); };
  auto init_with_std = [std_sqrt](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_sqrt(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::sqrt(z_t{a0,a1}), init_with_std(a0, a1), ulp);
};

TTS_CASE_TPL( "Check corner cases of sqrt", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 14;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto mone = eve::mone(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(mone,inf),//3
      c_t(nan,inf), //4
      c_t(one,nan), //5
      c_t(minf,one), //6
      c_t(inf,one), //7
      c_t(minf,-nan),//8
      c_t(inf,nan), //9
      c_t(nan,one), //10
      c_t(nan,nan),  //11
      c_t(T(4), zer),  //12
      c_t(nan,zer)  //13
    };

  std::array<c_t, N> results =
    {
      c_t(zer,zer), //0
      c_t(zer,zer),//1
      c_t(inf,inf), //2
      c_t(inf,inf),//3
      c_t(inf,inf), //4
      c_t(nan,nan), //5
      c_t(zer,inf), //6
      c_t(inf,zer), //7
      c_t(nan,minf),//8
      c_t(inf,nan), //9
      c_t(nan,nan), //10
      c_t(nan,nan),  //11
      c_t(T(2), zer),  //12
      c_t(nan,nan)  //13
    };

  using eve::conj;
  using eve::sqrt;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(sqrt(inputs[i]), results[i]);
    TTS_IEEE_EQUAL(sqrt(conj(inputs[i])), conj(sqrt(inputs[i])));
  }
};

TTS_CASE_TPL( "Check return types of sqrt", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 0.5;
  using c_t = eve::complex<T>;
  using eve::as;

  TTS_ULP_EQUAL(eve::sqrt(c_t(1)), c_t(1), 0);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::mone(as<T>()))), c_t(0, eve::one(as<T>())),ulp);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()))), c_t(eve::one(as<T>())),ulp);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::zero(as<T>()))), c_t(eve::zero(as<T>())),ulp);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::zero(as<T>()),eve::zero(as<T>()))), c_t(eve::zero(as<T>()),eve::zero(as<T>())),ulp);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::mzero(as<T>()),eve::zero(as<T>()))),c_t(eve::zero(as<T>()),eve::zero(as<T>())),ulp);
  TTS_ULP_EQUAL(eve::sqrt(c_t(0, 2)), c_t(1, 1), 1);
  for(T i=-5; i <=  T(5) ; i+= T(0.6))
  {
    for(T j =-5; j < T(5); j+= T(0.5))
    {
      TTS_ULP_EQUAL(eve::sqr(eve::sqrt(c_t(i, j))), c_t(i, j), 30.0);
    }
  }
   TTS_ULP_EQUAL(eve::sqrt(c_t(-4)), c_t(0, 2), 0);
   TTS_ULP_EQUAL(eve::sqrt(T(-4)), eve::nan(as<T>()), 0);
};
