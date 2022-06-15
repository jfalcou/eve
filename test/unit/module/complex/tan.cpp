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

TTS_CASE_WITH( "Check behavior of tan on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        ,tts::generate(tts::randoms(-10, 10)
                             ,tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::tan(eve::complex<e_t>(e, f)),  cv(std::tan(c_t(e, f))), 3.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of tan on wide"
        , eve::test::simd::ieee_reals
        ,tts::generate(tts::randoms(-10, 10)
                             ,tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return std::tan(c_t(x, y)); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::tan(z_t{a0,a1}), init_with_std(a0, a1), 2);
};


TTS_CASE_TPL( "Check corner cases of tan", eve::test::scalar::ieee_reals)
  <typename T>(tts::type<T>)
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
  using eve::conj;
  auto tangent = eve::tan;
  auto j = eve::i(eve::as<e_t>{});
  auto test_tangent = [j](auto x){return -j*eve::tanh(j*x); };
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(tangent(inputs[i]), test_tangent(inputs[i]));
    TTS_IEEE_EQUAL(tangent(-inputs[i]), tangent(inputs[i]));
    TTS_IEEE_EQUAL(tangent(conj(inputs[i])), conj(tangent(inputs[i])));
  }
};
