//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of is_not_less on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      for(auto g : a2)
      {
        for(auto h : a3)
        {
          auto z1 = doublereal_t(e, f);
          auto z2 = doublereal_t(g, h);
          TTS_EQUAL ( eve::is_not_less(z1, z2), !(z1 <   z2));
        }
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_not_less on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto z1 = make_doublereal(a0,a1);
  auto z2 = make_doublereal(a2, a3);
  TTS_EQUAL ( eve::is_not_less(z1, z2), !(z1 <   z2));
};
