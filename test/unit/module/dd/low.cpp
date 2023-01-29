//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_WITH( "Check behavior of low on scalar"
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
      TTS_EQUAL( eve::low(eve::dd<e_t>(e, f)), l );
      TTS_EQUAL( eve::low(eve::dd<e_t>(h, l)), l );
    }
  }
};

TTS_CASE_WITH( "Check behavior of low on wide"
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
  TTS_EQUAL( eve::low(make_dd(a0,a1)), l );
  TTS_EQUAL( eve::low(z_t{h, l }), l );
};
