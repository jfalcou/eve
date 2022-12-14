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


TTS_CASE_TPL( "Check corner cases of faddeeva", eve::test::scalar::ieee_reals)
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
      c_t(one,one),  //0
      c_t(half,one), //1
      c_t(10, 10), //2
      c_t(65, zer), //3
      c_t(0.01, one), //4
      c_t(1.0e-4, 2), //5
      c_t(0.785398163397448, zer), //6
      c_t(inf,zer), //7
      c_t(inf,nan), //8
    };

  std::array<c_t, N> results =
    {
      c_t(3.04744205256913e-01, 2.08218938202832e-01 ),
      c_t(3.91234021452136e-01, 1.27202410884648e-01 ),
      c_t(2.82794674542325e-02, 2.81384332763369e-02 ),
      c_t(0.00000000000000e+00, 8.68086731176095e-03 ),
      c_t(4.27568139375386e-01, 2.73204092253626e-03 ),
      c_t(2.55395675892478e-01, 1.06796461698883e-05 ),
      c_t(5.39641485816297e-01, 5.97805988669632e-01 ),
      c_t(0.00000000000000e+00, 0.00000000000000e+00 ),
      c_t(0.00000000000000e+00, 0.00000000000000e+00 )
    };
  using eve::conj;
  using eve::faddeeva;
  for(int i=0; i < N; ++i)
  {
    TTS_ULP_EQUAL(faddeeva(inputs[i]), results[i], 100)  << "i " << i << " -> " << inputs[i] <<  " -> " <<faddeeva(inputs[i])<<"\n";
  }
};
