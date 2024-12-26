//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <iomanip>
#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/module/math.hpp>

TTS_CASE_TPL ( "Check jacobi_elliptic over real"
             , eve::test::scalar::ieee_reals
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(1.0e-4, 1.0e-8);
  using a_t  = std::array<T, 7 >;
  a_t phi= {0.000000000000000e+00, 1.346396851538483e+00, 2.692793703076966e+00, 4.039190554615448e+00, 5.385587406153931e+00, 6.731984257692414e+00, 8.078381109230897e+00, };
  a_t m= {0.000000000000000e+00, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01, };
  a_t jz{0, 0.00223029473780215, -0.0161886778555027, 0.047304495923641, -0.0884024144241387, 0.111562414935445, -0.126058996008202, };

  //results are taken from boost jacobi_zeta outputs
  for(int i=0; i < 7; ++i)
  {
    TTS_RELATIVE_EQUAL(eve::jacobi_zeta(phi[i], m[i]), jz[i], pr);
  }
};
