//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of copysign on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z1 = dd_t(e, f/1000);
      auto z2 = dd_t(f, e/1000);
      auto am =  eve::sign(z1)!= eve::sign(z2) ? -z1 : z1;
      TTS_ULP_EQUAL ( eve::copysign(z1, z2), am, 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of copysign on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto z1 = make_dd(a0,a1);
  auto z2 = make_dd(a2, a3);
  auto am =  eve::if_else(eve::sign(z1)!= eve::sign(z2),  -z1,  z1);
  TTS_ULP_EQUAL ( eve::copysign(z1, z2), am, 0.5);
};
