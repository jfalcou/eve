//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of modf on scalar"
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
      auto z = eve::doublereal<e_t>(e, f);
      auto [fr, tr] = eve::modf(z);
      TTS_EQUAL(fr, eve::frac(z));
      TTS_EQUAL(tr, eve::trunc(z));
    }
  }
};

TTS_CASE_WITH( "Check behavior of modf on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto [f, t] = eve::modf(z);
  TTS_EQUAL ( f, eve::frac(z));
  TTS_EQUAL ( t, eve::trunc(z));

};
