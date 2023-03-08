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
  using boost::multiprecision::cpp_bin_float_quad;
   using f128 = cpp_bin_float_quad;
  static f128 P[6] = {
    f128("-9.889929415807650724957118893791829849557E-1"),
    f128("1.272297782199996882828849455156962260810E3"),
    f128("-4.249691853501233575668486667664718192660E5"),
    f128("5.160188250214037865511600561074819366815E7"),
    f128("-2.307030822693734879744223131873392503321E9"),
    f128("2.883414728874239697964612246732416606301E10")
  };

  static f128 Q[7] = {
    f128("1.000000000000000000000000000000000000000E0"),
    f128("-1.317243702830553658702531997959756728291E3"),
    f128("4.529422062441341616231663543669583527923E5"),
    f128("-5.733709132766856723608447733926138506824E7"),
    f128("2.758476078803232151774723646710890525496E9"),
    f128("-4.152206921457208101480801635640958361612E10"),
    f128("8.650244186622719093893836740197250197602E10")
   };
  std::cout << "P = " << std::endl;
  for (int i = 0; i < 6; ++i)
    std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(P[i]) << ", " << std::endl;

  std::cout << "Q = " << std::endl;
  for (int i = 0; i < 6; ++i)
    std::cout << "      " << std::hexfloat << std::setprecision(20) << cvt(Q[i]) << ", " << std::endl;
  TTS_EQUAL(0, 0);
  f128 dp1("3.321928094887362347870319429489390175864831");
  f128 dp2("3.01025390625e-1");
  f128 dp3("4.6050389811952137388947244930267681898814621E-6");
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp1) << std::endl;
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp2) << std::endl;
  std::cout <<  "     " << std::hexfloat << std::setprecision(20) << cvt(dp3) << std::endl;
};
