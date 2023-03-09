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

TTS_CASE_WITH( "Check behavior of frac on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  auto fr = [](auto x){ return x-bm::trunc(x);};
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_EQUAL ( tts::uptype(eve::frac(eve::doublereal<e_t>(e, f))), fr(tts::uptype(eve::doublereal<e_t>(e, f))));
    }
  }
};

TTS_CASE_WITH( "Check behavior of frac on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::frac, z));
  TTS_EQUAL ( eve::frac(z), az);
};
