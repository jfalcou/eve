//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of ipart on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      for(auto g : a2)
      {
        for(auto h : a3)
        {
          TTS_EQUAL( eve::ipart(eve::quaternion<e_t>(e, f, g, h)), f );
        }
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of ipart on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::quaternion<e_t>, typename T::cardinal_type>;

  TTS_EQUAL( eve::ipart(z_t(a0,a1,a2,a3)), a1 );
};
