//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of agd on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-3.14/2, 3.14/2)
                              , tts::randoms(-0.001, 0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto ep =  sizeof(e_t) == 4 ? 1.0E-9 :1.0e-22;
      auto z = eve::doublereal<e_t>(e, f);
      auto ac = eve::agd(z);
      auto bmbc = bm::asinh(bm::tan(tts::uptype(z)));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_RELATIVE_EQUAL(bc, ac, ep);
    }
  }
};

//TODO
// TTS_CASE_WITH( "Check behavior of agd on wide"
//              , eve::test::simd::ieee_reals
//              , tts::generate ( tts::randoms(-3.14/2, 3.14/2)
//                              , tts::randoms(-0.001, 0.001)
//                              )
//              )
//   <typename T>(T const& a0, T const& a1 )
// {
//   auto z = make_doublereal(a0,a1);
//   auto az = decltype(z)(eve::detail::map(eve::agd, z));
//   auto cz = eve::agd(z);
//   TTS_ULP_EQUAL(cz, az, 2.0e+4);
// };
