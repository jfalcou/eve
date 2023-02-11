//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

eve::doublereal<double> cvt(boost::multiprecision::cpp_bin_float_quad a)
{
  double h = double(a);
  double l = double(a-h);
  return eve::doublereal<double>(h, l);
}
eve::doublereal<float> cvt(double a)
{
  float h = float(a);
  float l = float(a-h);
  return eve::doublereal<float>(h, l);
}

TTS_CASE_WITH( "Check behavior of exp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& , T const& )
{
  static double P[4] = {
 4.09962519798587023075E-2,
 1.17452732554344059015E1,
 4.06717289936872725516E2,
 2.39423741207388267439E3,
  };
  static double Q[4] = {
    1.0,
    8.50936160849306532625E1,
    1.27209271178345121210E3,
    2.07960819286001865907E3,
  };

  std::cout << "P = " << std::endl;
  for (int i = 0; i < 3; ++i)
    std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(P[i]) << ", " << std::endl;

  std::cout << "Q = " << std::endl;
  for (int i = 0; i < 4; ++i)
    std::cout << "      " << std::hexfloat << std::setprecision(20) << cvt(Q[i]) << ", " << std::endl;
  TTS_EQUAL(0, 0);
  double dp1(3.32192809488736234787e0 );
  double dp2( 3.01025390625000000000E-1 );
  double dp3(4.60503898119521373889E-6);
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp1) << std::endl;
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp2) << std::endl;
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp3) << std::endl;





};
