//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of next on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z =  eve::doublereal<e_t>(e, f);
      auto n = eve::next(z);
      TTS_GREATER(n, z);
      auto np = eve::prev(n);
      TTS_EQUAL(np, z);
      auto npp = eve::prev(np);
      TTS_LESS(npp, z);
    }
  }

//   for(auto e : a0)
//   {
//     for(auto f : a1)
//     {
//       auto z =  eve::doublereal<e_t>(e, f);
//       auto n = eve::next(z);
//       TTS_GREATER(n, z);
//       auto np = eve::prev(n);
//       TTS_EQUAL(np, z);
//       auto npp = eve::prev(np);
//       TTS_LESS(npp, z);
//     }
//   }
};



// TTS_CASE_WITH( "Check behavior of next on wide"
//         , eve::test::simd::ieee_reals
//         , tts::generate ( tts::randoms(-10, 10)
//                               , tts::randoms(-10, 10)
//                               )
//         )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//       auto g = eve::next(z) > z;
//       std::cout << g << std::endl;
// //  auto z = make_doublereal(a0,a1);
// //  TTS_EXPECT( eve::next(z) > z);
// };
