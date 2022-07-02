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

TTS_CASE_WITH( "Check behavior of log on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::log(eve::complex<e_t>(e, f)),  cv(std::log(c_t(e, f))), 4);
    }
  }
};

TTS_CASE_WITH( "Check behavior of log on wide"
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
  auto std_ch = [](auto x, auto y){return cv(std::log(c_t(x, y))); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::log(z_t{a0,a1}), init_with_std(a0, a1), 2);
};

TTS_CASE_TPL( "Check corner cases of log", eve::test::scalar::ieee_reals)
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
  auto pi = eve::pi(as<T>());
  auto pio_2 = eve::pio_2(as<T>());
  auto pio_4 = eve::pio_4(as<T>());
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

  std::array<c_t, N> results =
    {
      c_t(minf,pi),   //0
      c_t(minf,zer),  //1
      c_t(inf,pio_2), //2
      c_t(nan,nan),   //3
      c_t(inf,pi),    //4
      c_t(inf,pi),    //5
      c_t(inf,zer),   //6
      c_t(inf,zer),  //7
      c_t(inf,pio_4), //8
      c_t(inf, nan),  //9
      c_t(inf,nan),   //10
      c_t(nan,nan),   //11
      c_t(inf,nan),   //12
      c_t(nan,nan)    //13
    };

  using eve::conj;
  using eve::log;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(log(inputs[i]), results[i]) << "i " << i << " -> " << inputs[i] << "\n";
    TTS_IEEE_EQUAL(log(conj(inputs[i])), conj(log(inputs[i])));
  }
};

TTS_CASE_TPL( "Check return types of eve::log", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using c_t = eve::complex<T>;

  TTS_ULP_EQUAL((eve::log)(c_t(eve::mone(as<T>()))), c_t(eve::zero(as<T>()), eve::pi(as<T>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one(as<T>()))), c_t(eve::zero(as<T>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::zero(as<T>()), eve::one(as<T>()))),c_t(eve::zero(as<T>()), eve::pio_2(as<T>())), 0.5);

  TTS_ULP_EQUAL(eve::log(c_t(-4, 0)), c_t(eve::log(T(4)), eve::pi(as<T>())), 0);
  TTS_ULP_EQUAL(eve::log(T(-4)), eve::nan(as<T>()), 0);
};
