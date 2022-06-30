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

TTS_CASE_WITH( "Check behavior of log10 on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  auto std_log10 = [](auto x){return std::log(x)/eve::log_10(eve::as<e_t>()); };
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::log10(eve::complex<e_t>(e, f)),  cv(std_log10(c_t(e, f))), 2);
    }
  }
};

TTS_CASE_WITH ( "Check behavior of log10 on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-10, 10), tts::randoms(-10, 10))
              )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::as_complex_t<T>;
  TTS_ULP_EQUAL(eve::log10(z_t{a0,a1}), eve::log(z_t{a0, a1})/eve::log_10(eve::as<e_t>()), 2);
};

TTS_CASE_TPL( "Check corner cases of eve::log10", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 14;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(mzer,zer), //0
      c_t(zer,zer),  //1
      c_t(one,inf),  //2
      c_t(one,nan),  //3
      c_t(minf,one), //4
      c_t(minf,zer),//5
      c_t(inf,one),  //6
      c_t(inf,zer), //7
      c_t(inf,inf),  //8
      c_t(inf, nan), //9
      c_t(minf,nan), //10
      c_t(nan,one),  //11
      c_t(nan,inf),  //12
      c_t(nan,nan)   //13
    };
  using eve::conj;
  using eve::log10;
  auto std_log10 = [](auto x){return eve::log(x)/eve::log_10(eve::as<T>()); };
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(log10(inputs[i]), std_log10(inputs[i]));
    TTS_IEEE_EQUAL(log10(conj(inputs[i])), conj(log10(inputs[i])));
  }
};

TTS_CASE_TPL( "Check return types of eve::log10", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::pedantic;
  using c_t = eve::complex<T>;

  TTS_ULP_EQUAL((eve::log10)(c_t(eve::mone(as<T>()))), c_t(eve::zero(as<T>()), eve::pi(as<T>())/eve::log_10(as<T>())), 0.5);
  TTS_ULP_EQUAL((eve::log10)(c_t(eve::one(as<T>()))), c_t(eve::zero(as<T>())), 0.5);
  TTS_ULP_EQUAL((eve::log10)(c_t(eve::zero(as<T>()), eve::one(as<T>()))),c_t(eve::zero(as<T>()), eve::pio_2(as<T>())/eve::log_10(as<T>())), 0.5);

  TTS_ULP_EQUAL(eve::log10(c_t(-4, 0)), c_t(eve::log10(T(4)), eve::pi(as<T>())/eve::log_10(as<T>())), 0);
  TTS_ULP_EQUAL(eve::log10(T(-4)), eve::nan(as<T>()), 0);
};
