//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_WITH( "Check behavior of sign on scalar"
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
//      auto [h, l] = eve::dd<e_t>(e, f);
//      TTS_EQUAL( eve::sign(eve::dd<e_t>(e, f)), eve::dd<e_t>(ch, cl) ) << eve::dd<e_t>(e, f) << '\n' ;
      if constexpr(sizeof(e_t) == 4)
      {
        TTS_ULP_EQUAL ( eve::to_double(eve::sign(eve::dd<e_t>(e, f))), eve::sign(eve::to_double(eve::dd<e_t>(e, f))), 32);
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of sign on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto z = make_dd(a0,a1);
  if constexpr(sizeof(e_t) == 4)
  {
    TTS_ULP_EQUAL ( eve::to_double(eve::sign(z)), eve::sign(eve::to_double(z)), 32);
  }
};
