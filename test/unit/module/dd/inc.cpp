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

TTS_CASE_WITH( "Check behavior of inc on scalar"
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
     TTS_EQUAL ( tts::uptype(eve::inc(eve::dd<e_t>(e, f))), tts::uptype(eve::dd<e_t>(e, f)+1));
    }
  }
};

TTS_CASE_WITH( "Check behavior of inc on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::inc, z));
  TTS_EQUAL ( eve::inc(z), az);
};
