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


TTS_CASE_TPL( "Check corner cases of erfcx", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 9;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto half= eve::half(as<T>());

  std::array<c_t, N> inputs =
    {
      c_t(one,one),   //0
      c_t(half,one),  //1
      c_t(10, 10),    //2
      c_t(65, zer),   //3
      c_t(0.01, one), //4
      c_t(1.0e-4, 2), //5
      c_t(0.785398163397448, zer), //6
      c_t(inf,zer),   //7
      c_t(nan,nan)    //8
    };

  std::array<c_t, N> results =
    {
      c_t(3.04744205256913e-01, -2.08218938202832e-01 ), //0
      c_t(3.54900332867578e-01, -3.42871719131101e-01 ), //1
      c_t(2.82794674542325e-02, -2.81384332763369e-02 ), //2
      c_t(eve::erfcx(T(65)), zer), //c_t(8.67881291138928e-03, +0.00000000000000e+00 ), //3
      c_t(3.68702417397766e-01, -5.99851994495788e-01 ), //4
      c_t(1.83388101767463e-02, -3.40018889576381e-01 ), //5
      c_t(4.94195834537586e-01, +0.00000000000000e+00 ), //6
      c_t(eve::erfcx(inf), zer), //c_t(0.00000000000000e+00, +0.00000000000000e+00 ), //7
      c_t(nan                ,  nan                   )  //8
    };
  using eve::conj;
  using eve::erfcx;
  for(int i=0; i < N; ++i)
  {
    TTS_ULP_EQUAL(erfcx(inputs[i]), results[i], 100)  << "i " << i << " -> " << inputs[i] <<  " -> " <<erfcx(inputs[i])<<"\n";
  }
  std::cout << erfcx(eve::inf(as(T()))) << std::endl;
};
