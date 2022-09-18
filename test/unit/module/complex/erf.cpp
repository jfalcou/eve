//==================================================================================================
/**
  EVE - Erfressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>


TTS_CASE_TPL( "Check corner cases of erf", eve::test::scalar::ieee_reals)
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
      c_t(nan,inf), //0
      c_t(zer, zer),     //1
      c_t(nan,nan), //2
      c_t(1,zer), //3
      c_t(nan,nan), //4
      c_t(1,zer), //5
      c_t(1,zer), //6
      c_t(1,zer),//7
      c_t(nan,nan), //8
      c_t(nan,nan), //9
      c_t(nan,nan), //10
      c_t(nan,nan)  //11
    };
  using eve::conj;
  using eve::erf;
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(erf(inputs[i]), results[i])  << "i " << i << " -> " << inputs[i] <<  " -> " <<erf(inputs[i])<<"\n";
    TTS_IEEE_EQUAL(erf(conj(inputs[i])), conj(erf(inputs[i])));
  }
};
