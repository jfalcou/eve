//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_WITH( "Check behavior of epsilon on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using dd_t =eve::dd<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
       auto z = dd_t(e, f);
       TTS_EQUAL ( eve::epsilon(z), eve::dist(eve::abs(z), eve::next(eve::abs(z))));
    }
  }
};

TTS_CASE_WITH( "Check behavior of epsilon on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = eve::dist(eve::abs(z), eve::next(eve::abs(z))); ;
  TTS_EQUAL ( eve::epsilon(z), az);
};
