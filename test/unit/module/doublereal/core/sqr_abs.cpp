//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of sqr_abs on scalar"
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
//      auto [h, l] = eve::doublereal<e_t>(e, f);
//      TTS_EQUAL( eve::sqr_abs(eve::doublereal<e_t>(e, f)), eve::doublereal<e_t>(ch, cl) ) << eve::doublereal<e_t>(e, f) << '\n' ;
      if constexpr(sizeof(e_t) == 4)
      {
        TTS_ULP_EQUAL ( eve::to_double(eve::sqr_abs(eve::doublereal<e_t>(e, f))), eve::sqr_abs(eve::to_double(eve::doublereal<e_t>(e, f))), 32);
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of sqr_abs on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto z = make_doublereal(a0,a1);
  if constexpr(sizeof(e_t) == 4)
  {
    TTS_ULP_EQUAL ( eve::to_double(eve::sqr_abs(z)), eve::sqr_abs(eve::to_double(z)), 32);
  }
};
