//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>




TTS_CASE_WITH( "Check behavior of atan on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-0.0001, 0.0001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{

//   auto func = [](eve::dd<double> xx)
//     {
//       auto x2 = eve::sqr(xx);
//       using dd_t = eve::dd<double>;
//       auto px = ((((dd_t(5053)/75075)*x2 + dd_t(383)/585)*x2 + dd_t(23)/15)*x2 + dd_t(1));
//       auto qx = (((((dd_t(7)/1287)*x2 + dd_t(28)/143)*x2 + dd_t(14)/13)*x2 + dd_t(28)/15)*x2 + 1);
//       return xx*px/qx;
//     };

  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
//  if constexpr(sizeof(e_t) == 8)
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
      std::cout << "ef " << e << ", " << f << std::endl;
      std::cout << "hl " << eve::high(z) << ", " << eve::low(z) << std::endl;
      auto ac = eve::atan(z);
      auto sc = eve::asin(z/eve::sqrt(eve::inc(eve::sqr(z))));
//      auto fac= func(z);
      auto bmbc = bm::atan(tts::uptype(z));
      eve::dd<e_t> bc(bmbc);
       std::cout << "z    " << z     << std::endl;
       std::cout << "bc   " << bc    << std::endl;
       std::cout << "ac   " << ac    << std::endl;
       std::cout << "sc   " << sc    << std::endl;
       std::cout << "bc-ac" << bc-ac << std::endl;
       std::cout << "bc-sc" << bc-sc << std::endl;
//       std::cout << ac-fac << std::endl;
      TTS_ULP_EQUAL(bc, sc, 16);
      TTS_ULP_EQUAL(bc, ac, 16);
    }
  }
};

TTS_CASE_WITH( "Check behavior of atan on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::atan, z));
  auto cz = eve::atan(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
