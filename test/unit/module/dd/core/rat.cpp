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

TTS_CASE_WITH( "Check behavior of rat on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(1, 10)
                             , tts::randoms(0, 0.01)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using dd_t =eve::dd<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
       auto z = dd_t(e, f);
       auto [n, d] = eve::rat(z);
       TTS_RELATIVE_EQUAL (n, z*d, 1.0e-4);
    }
  }
};

TTS_CASE_WITH( "Check behavior of rat on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(1, 10)
                             , tts::randoms(0, 0.01)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto [n, d] = eve::rat(z);
  TTS_RELATIVE_EQUAL (n, z*d, 1.0e-4);
};
