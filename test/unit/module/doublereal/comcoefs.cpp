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
    f128("6.781965388610215141646963666801877147888E1"),
    f128("4.930988843306627886355612005613845141123E4"),
    f128("9.112966716416345527154611203937593471620E6"),
    f128("5.880306836049276068401249115246879608067E8"),
    f128("1.294143447497151402129871056524193102276E10"),
    f128("6.737236378815985929063482575381049393067E10")
  };
  static f128 Q[7] = {
    f128("1.000000000000000000000000000000000000000E0"),
    f128("2.269602544366008200564158516293459788943E3"),
    f128("7.712352920905011963059413773034169405418E5"),
    f128("8.312829542416079818945631366865677745737E7"),
    f128("3.192530874297321568824835872165913128965E9"),
    f128("3.709588725051672862074295071447979432510E10"),
    f128("5.851889165195258152098281616369230806944E10"),
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
