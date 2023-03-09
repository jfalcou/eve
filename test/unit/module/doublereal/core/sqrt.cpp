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

TTS_CASE_WITH( "Check behavior of sqrt on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      TTS_ULP_EQUAL ( eve::sqrt(z), tts::to_doublereal<e_t>(sqrt(tts::uptype(z))),0.5 );
    }
  }
};

TTS_CASE_WITH( "Check behavior of sqrt on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::sqrt, z));
  TTS_ULP_EQUAL ( eve::sqrt(z), az, 1.0);
};
