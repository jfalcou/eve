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
#include <cmath>

// TTS_CASE_WITH( "Check behavior of fma on scalar"
//              , tts::bunch<eve::test::scalar::ieee_reals>
//              , tts::generate ( tts::randoms(-10, 10)
//                              , tts::randoms(-10, 10)
//                              )
//              )
//   <typename T>(T const& a0, T const&  a1)
// {
//   using e_t = typename T::value_type;
//   using doublereal_t = eve::doublereal<e_t>;
//   auto thresh = eve::eps(eve::as<doublereal_t>())*20;
//   for(auto f : a1)
//   {
//     auto z3 = doublereal_t(f, f/2);
//     for(auto e : a0)
//     {
//       auto z1 = doublereal_t(e, f);
//       auto z2 = doublereal_t(f, e);
//       auto adiff = eve::abs(eve::numeric(eve::fma)(z1, z2, z3)-(z1*z2+z3));
//       TTS_EXPECT(adiff < thresh);
//     }
//   }
// };

TTS_CASE_WITH( "Check behavior of fma on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z1 = make_doublereal(a0,a1);
  auto z2 = make_doublereal(a1,a0);
  auto z3 = make_doublereal(a1,a1/2);
  auto thresh = eve::eps(eve::as(z1))*20;
  auto adiff = eve::abs(eve::numeric(eve::fma)(z1, z2, z3)-(z1*z2+z3));
  std::cout << "adiff " << adiff << std::endl;
  TTS_EXPECT(eve::all(adiff < thresh));
};
