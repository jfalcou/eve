//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>
#include <cmath>

TTS_CASE_WITH( "Check behavior of fma on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const&  a1)
{
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  if constexpr(sizeof(e_t)!=  0)
  {
    for(auto f : a1)
    {
      auto z3 = dd_t(f, f/2);
      for(auto e : a0)
      {
        auto z1 = dd_t(e, f);
        auto z2 = dd_t(f, e);
        TTS_EQUAL ( tts::uptype(eve::fma(z1, z2, z3)), tts::uptype(z1)* tts::uptype(z2)+ tts::uptype(z3));
        std::cout << (tts::uptype(eve::fma(z1, z2, z3))-(tts::uptype(z1)* tts::uptype(z2)+ tts::uptype(z3))) << std::endl;
        std::cout << eve::fms(z1, z2, z3) << std::endl;
        std::cout << sizeof(e_t) <<  " -> eps = " << eve::eps(eve::as(z1)) << std::endl;
      }
    }
  }
};

// TTS_CASE_WITH( "Check behavior of fma on wide"
//         , eve::test::simd::ieee_reals
//         , tts::generate ( tts::randoms(-10, 10)
//                               , tts::randoms(-10, 10)
//                               )
//         )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//   if constexpr(sizeof(e_t) == 4)
//   {
//     auto z1 = make_dd(a0,a1);
//     auto z2 = make_dd(a1,a0);
//     TTS_EQUAL ( eve::to_double(eve::fma(z1, z2)), eve::fma(eve::to_double(z1), to_double(z2)));
//   }
// };
