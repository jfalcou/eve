//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_WITH( "Check behavior of high on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto [h, l] = eve::two_add(e, f);
      TTS_EQUAL( eve::high(eve::dd<e_t>(e, f)), h );
      TTS_EQUAL( eve::high(eve::dd<e_t>(h, l)), h );
    }
  }
};

TTS_CASE_WITH( "Check behavior of high on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::dd<e_t>, typename T::cardinal_type>;
  auto [h, l] = eve::two_add(a0, a1);
//  TTS_EQUAL( eve::high(z_t{a0,a1}), h ); //TODO still not ok
  TTS_EQUAL( eve::high(make_dd(a0,a1)), h );
  TTS_EQUAL( eve::high(z_t{h, l }), h );
};
