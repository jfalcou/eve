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

TTS_CASE_WITH( "Check behavior of atan on scalar"
        ,  tts::bunch<eve::test::scalar::ieee_reals>
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
      TTS_RELATIVE_EQUAL(eve::atan(eve::complex<e_t>(e, f)),  cv(std::atan(c_t(e, f))), 0.001);
    }
  }
};

TTS_CASE_WITH( "Check behavior of atan on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return cv(std::atan(c_t(x, y))); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_RELATIVE_EQUAL(eve::atan(z_t{a0,a1}), init_with_std(a0, a1), 0.001);
};


TTS_CASE_TPL( "Check return types of eve::abs", eve::test::scalar::ieee_reals)
  <typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 16;
  std::array<c_t, N> inputs =
    { c_t(eve::zero(as<T>()),eve::zero(as<T>())),//0
      c_t(eve::inf(as<T>()),eve::zero(as<T>())), //1
      c_t(eve::minf(as<T>()),eve::zero(as<T>())),//2
      c_t(eve::nan(as<T>()),eve::zero(as<T>())), //3
      c_t(eve::zero(as<T>()),eve::inf(as<T>())), //4
      c_t(eve::inf(as<T>()),eve::inf(as<T>())),  //5
      c_t(eve::minf(as<T>()),eve::inf(as<T>())), //6
      c_t(eve::nan(as<T>()),eve::inf(as<T>())),  //7
      c_t(eve::zero(as<T>()),eve::minf(as<T>())),//8--
      c_t(eve::inf(as<T>()),eve::minf(as<T>())), //9
      c_t(eve::minf(as<T>()),eve::minf(as<T>())),//10
      c_t(eve::nan(as<T>()),eve::minf(as<T>())), //11
      c_t(eve::zero(as<T>()),eve::nan(as<T>())), //12
      c_t(eve::inf(as<T>()),eve::nan(as<T>())),  //13
      c_t(eve::minf(as<T>()),eve::nan(as<T>())), //14
      c_t(eve::nan(as<T>()),eve::nan(as<T>())),  //15
    };

  auto atanine = (eve::atan);
  auto tatanine= [](auto z){return -(eve::i*eve::atanh(eve::i*z));};
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(atanine(inputs[i]), -atanine(-inputs[i]));
    TTS_IEEE_EQUAL(atanine(inputs[i]), tatanine(inputs[i]));
  }
};
