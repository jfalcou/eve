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

TTS_CASE_WITH( "Check behavior of acot on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-0.0001, 0.0001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
//  if constexpr(sizeof(e_t) == 8)
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
//       std::cout << "ef " << e << ", " << f << std::endl;
//       std::cout << "hl " << eve::high(z) << ", " << eve::low(z) << std::endl;
      auto ac = eve::acot(z);
      auto bmbc = bm::atan(tts::uptype(eve::rec(z)));
      eve::dd<e_t> bc(bmbc);
       std::cout << "z    " << z     << std::endl;
       std::cout << "bc   " << bc    << std::endl;
       std::cout << "ac   " << ac    << std::endl;
       std::cout << "bc-ac" << bc-ac << std::endl;
      TTS_ULP_EQUAL(bc, ac, 1000);
    }
  }
  dd<double >  pio2(1.5707963267948965579989817342720925807952880859375); 
  dd<double >  err(6.123233995736766035868820147291983023128460623388e-17, 1.5707963267948965579989817342720925807952880859375);
  

};

// TTS_CASE_WITH( "Check behavior of acot on wide"
//              , eve::test::simd::ieee_reals
//              , tts::generate ( tts::randoms(-10, 10)
//                              , tts::randoms(-1, 1)
//                              )
//              )
//   <typename T>(T const& a0, T const& a1 )
// {
//   auto z = make_dd(a0,a1);
//   auto az = decltype(z)(eve::detail::map(eve::acot, z));
//   auto cz = eve::acot(z);
//   TTS_ULP_EQUAL(cz, az, 0.5);
// };
