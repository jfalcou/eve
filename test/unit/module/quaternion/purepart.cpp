//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of purepart on scalar"
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
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto a = eve::purepart(eve::quaternion<e_t>(a0[i],a1[i],a2[i],a3[i]));
    TTS_EQUAL( a1[i], get<0>(a) );
    TTS_EQUAL( a2[i], get<1>(a) );
    TTS_EQUAL( a3[i], get<2>(a) );
  }
};

TTS_CASE_WITH( "Check behavior of purepart on wide"
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

  auto a = eve::purepart(z_t(a0,a1,a2,a3));
  TTS_EQUAL( a1, get<0>(a));
  TTS_EQUAL( a2, get<1>(a));
  TTS_EQUAL( a3, get<2>(a));
};
