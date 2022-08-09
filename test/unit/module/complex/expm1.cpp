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

template < typename T >
auto cv(std::complex <T> sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of expm1 on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              ,tts::generate(tts::randoms(-10, 10),tts::randoms(-10, 10))
              )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
//  using c_t = std::complex<e_t>;
  using z_t = eve::as_complex_t<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_RELATIVE_EQUAL( eve::expm1(eve::complex<e_t>(e, f))
                        , eve::dec(eve::exp(z_t(e, f)))
                        , 4e-3
                        );
    }
  }
};

TTS_CASE_TPL( "Check corner cases of expm1", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
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

  std::array<c_t, N> results =
    {
      c_t(zer,zer), //0
      c_t(nan,nan), //1
      c_t(nan,nan), //2
      c_t(nan,nan), //3
      c_t(nan,nan), //4
      c_t(inf,zer), //5
      inf*eve::exp_i(one)-one, //6
      c_t(inf,nan),//7
      c_t(inf,nan), //8
      c_t(nan,zer), //9
      c_t(nan,nan), //10
      c_t(nan,nan)  //11
    };
  using eve::conj;
  using eve::expm1;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(expm1(inputs[i]), results[i]) << "i " << i << " -> " << inputs[i] << "\n";
    TTS_IEEE_EQUAL(expm1(conj(inputs[i])), conj(expm1(inputs[i])));
  }
 auto eps = eve::eps(as<T>());
 TTS_ULP_EQUAL(eve::expm1(c_t{eps, zer}),   (c_t{eps, zer}), 0.5);
 TTS_ULP_EQUAL(eve::expm1(c_t{zer, eps}),   (c_t{-eve::sqr(eps)/2, eps}), 0.5);
};
