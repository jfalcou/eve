//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of frac on scalar"
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
//      TTS_EQUAL( eve::frac(eve::doublereal<e_t>(e, f)), eve::doublereal<e_t>(ch, cl) ) << eve::doublereal<e_t>(e, f) << '\n' ;
      if constexpr(sizeof(e_t) == 4)
      {
        TTS_EQUAL ( eve::to_double(eve::frac(eve::doublereal<e_t>(e, f))), eve::frac(eve::to_double(eve::doublereal<e_t>(e, f))));
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of frac on wide"
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
    TTS_EQUAL ( eve::to_double(eve::frac(z)), eve::frac(eve::to_double(z)));

    auto z = eve::doublereal<e_t>((1ll << 40)+12);
    TTS_EQUAL ( eve::to_double(eve::frac(z)), eve::frac(eve::to_double(z)));
  }
};
