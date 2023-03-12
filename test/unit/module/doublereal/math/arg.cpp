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

TTS_CASE_WITH( "Check behavior of arg on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-0.5, 0.5)
                              , tts::randoms(-0.5, 0.5)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      auto ac = eve::arg(z);
      auto bmbc = eve::is_negative(z) ? eve::pi(eve::as(z)) : eve::zero(eve::as(z));
      eve::doublereal<e_t> bc(bmbc);
      TTS_ULP_EQUAL(bc, ac, 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of arg on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-0.7, 0.7)
                             , tts::randoms(-0.3, 0.3)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::arg, z));
  auto cz = eve::arg(z);
  TTS_EQUAL ( cz, az);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
