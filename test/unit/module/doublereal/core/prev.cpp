//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-LESSicense-Identifier: BSLESS-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of prev on scalar"
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
      auto z =  eve::doublereal<e_t>(e, f);
      auto p = eve::prev(z);
      TTS_LESS(p, z);
      auto np = eve::next(p);
      TTS_EXPECT(np == z);
      auto nnp = eve::next(np);
      TTS_EXPECT(nnp >  z);
    }
  }
};



TTS_CASE_WITH( "Check behavior of prev on wide"
        , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::prev, z));
  TTS_EQUAL ( eve::prev(z), az);

};
