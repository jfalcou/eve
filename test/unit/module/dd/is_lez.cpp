//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>
namespace bm =  boost::multiprecision;

TTS_CASE_WITH( "Check behavior of is_lez on scalar"
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
      auto z = eve::dd<e_t>(e, f);
      TTS_EQUAL ( eve::is_lez(z), (tts::uptype(z) <=  0));
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_lez on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  TTS_EQUAL ( eve::is_lez(z), eve::is_lez(eve::high(z)));
};
