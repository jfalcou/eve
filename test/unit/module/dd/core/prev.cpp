//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-LESSicense-Identifier: BSLESS-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_WITH( "Check behavior of prev on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z =  eve::dd<e_t>(e, f);
      auto n = eve::prev(z);
      TTS_LESS(n, z);
      auto np = eve::next(n);
      TTS_EQUAL(np, z);
      auto npp = eve::next(np);
      TTS_GREATER(npp, z);
      }
    }

//   for(auto e : a0)
//   {
//     for(auto f : a1)
//     {
//       auto z =  eve::dd<e_t>(e, f);
//       auto n = eve::prev(z, 3);
//       TTS_LESS(n, z);
//       auto np = eve::next(n, 3);
//       TTS_EQUAL(np, z);
//       auto npp = eve::next(np, 4);
//       TTS_GREATER(npp, z);

//     }
//   }
};



// TTS_CASE_WITH( "Check behavior of prev on wide"
//         , eve::test::simd::ieee_reals
//         , tts::generate ( tts::randoms(-10, 10)
//                               , tts::randoms(-10, 10)
//                               )
//         )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//       auto g = eve::prev(z) > z;
//       std::cout << g << std::endl;
// //  auto z = make_dd(a0,a1);
// //  TTS_EXPECT( eve::prev(z) > z);
// };
