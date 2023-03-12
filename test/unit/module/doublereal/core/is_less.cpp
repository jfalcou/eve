//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of is_less on scalar"
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
      auto z1 = doublereal_t(e, f/1000);
      auto z2 = doublereal_t(f, e/1000);
      TTS_EQUAL ( eve::is_less(z1, z2), (z1 < z2));
      TTS_EQUAL ( eve::is_less(z1, e), z1 < doublereal_t(e));
      TTS_EQUAL ( eve::is_less(f, z1),doublereal_t(f) < z1);
      TTS_EQUAL ( (z1 < e), (z1 < make_doublereal(e, eve::as(z1))));
      TTS_EQUAL ( (z1 < eve::doublereal<e_t>(1.0)), (z1 < make_doublereal(1.0, eve::as(z1))));
      TTS_EQUAL ( (z1 < 1.0), z1 < make_doublereal(1.0, eve::as(z1)));
      TTS_EQUAL ( (z1 < 1), z1 < make_doublereal(1, eve::as(z1)));
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_less on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto z1 = make_doublereal(a0,a1/1000);
  auto z2 = make_doublereal(a1,a0/1000);
  TTS_EQUAL ( eve::is_less(z1, z2), (z1 < z2));
  TTS_EQUAL ( eve::is_less(z1, a1), (z1 < make_doublereal(a1, eve::as(z1))));
  TTS_EQUAL ( eve::is_less(z1, 1.0), z1 < make_doublereal(1.0, eve::as(z1)));
  TTS_EQUAL ( (z1 < z2), (z1 < z2));
  TTS_EQUAL ( (z1 < a1), (z1 < make_doublereal(a1, eve::as(z1))));
  TTS_EQUAL ( (z1 < eve::doublereal<e_t>(1.0)), (z1 < make_doublereal(1.0, eve::as(z1))));
  TTS_EQUAL ( (z1 < 1.0), z1 < make_doublereal(1.0, eve::as(z1)));
  TTS_EQUAL ( (z1 < 1), z1 < make_doublereal(1, eve::as(z1)));

};
