//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of negabsmax on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
     if constexpr(sizeof(e_t) == 4)
      {
        auto z1 = doublereal_t(e, f);
        auto z2 = doublereal_t(f, e);
        TTS_EQUAL ( eve::to_double(eve::negabsmax(z1, z2)), eve::negabsmax(eve::to_double(z1), to_double(z2)));
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of negabsmax on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  if constexpr(sizeof(e_t) == 4)
  {
    auto z1 = make_doublereal(a0,a1);
    auto z2 = make_doublereal(a1,a0);
    TTS_EQUAL ( eve::to_double(eve::negabsmax(z1, z2)), eve::negabsmax(eve::to_double(z1), to_double(z2)));
  }
};
