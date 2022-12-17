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


TTS_CASE_TPL( "Check corner cases of erfi", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 11;
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
      c_t(65, zer),   //3*
      c_t(0.01, one), //4
      c_t(1.0e-4, 2), //5
      c_t(0.785398163397448, zer), //6
      c_t(inf,zer),   //7
      c_t(nan,nan),   //8
      c_t(one, 0 ),   //9
      c_t(half, 0)    //10
    };

  std::array<c_t, N> results =
    {
      c_t(1.90453469237835e-01, 1.31615128169795e+00), //0
      c_t(1.87973467223383e-01, 9.50709728318957e-01), //1
      c_t(-1.09876846081940e-02, 9.61649374272475e-01), //2
      c_t(inf,                  0.00000000000000e+00), //3
      c_t(4.15093659812155e-03, 8.42742304391298e-01), //4
      c_t(2.06669848718624e-06, 9.95322265432292e-01), //5
      c_t(1.10778360148748e+00, 0.00000000000000e+00), //6
      c_t(inf,                  0.00000000000000e+00), //7
      c_t(nan,                  nan                 ), //8
      c_t(1.65042575879754e+00, 0.00000000000000e+00), //9
      c_t(6.14952094696511e-01, 0.00000000000000e+00)  //10
    };
  using eve::conj;
  using eve::erfi;
  for(int i=0; i < N; ++i)
  {
    TTS_ULP_EQUAL(erfi(inputs[i]), results[i], 100)  << "i " << i << " -> " << inputs[i] <<  " -> " <<erfi(inputs[i])<<"\n";
  }
  std::cout << erfi(eve::inf(as(T()))) << std::endl;
};
