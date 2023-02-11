//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>


TTS_CASE_WITH( "Check behavior of rec on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(2.5, 10)
                             , tts::randoms(0, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
//       TTS_ULP_EQUAL(eve::domain::doublereal(eve::rec)(e), eve::rec(eve::doublereal<e_t>(e)), 0.5);
//       TTS_ULP_EQUAL(eve::domain::doublereal(eve::rec)(e), eve::domain::doublereal(eve::rec)(eve::doublereal<e_t>(e)), 0.5);
      auto z = eve::doublereal<e_t>(e, f);
      TTS_ULP_EQUAL ( eve::rec(z), eve::one(eve::as(z))/z, 0.5);
    }
  }
};


TTS_CASE_WITH( "Check behavior of rec on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = eve::make_doublereal(a0,a1);
  TTS_ULP_EQUAL ( eve::rec(z), eve::one(eve::as(z))/z, 0.5);

//   TTS_ULP_EQUAL(eve::domain::doublereal(eve::rec)(a0), eve::rec(eve::make_doublereal(a0, eve::zero(eve::as(a0)))), 0.5);
//   TTS_ULP_EQUAL(eve::domain::doublereal(eve::rec)(a0), eve::domain::doublereal(eve::rec)(eve::make_doublereal(a0, eve::zero(eve::as(a0)))), 0.5);

};
