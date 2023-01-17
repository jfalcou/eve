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

TTS_CASE_WITH( "Check behavior of is_odd on scalar"
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
      auto tz = eve::trunc(z);
      TTS_EQUAL ( eve::is_odd(z),  eve::is_even(eve::inc(z)));
      TTS_EQUAL ( eve::is_odd(tz), eve::is_even(eve::inc(tz)));
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_odd on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto tz = eve::trunc(z);
  TTS_EQUAL ( eve::is_odd(z), eve::is_even(eve::inc(z)));
  TTS_EQUAL ( eve::is_odd(tz), eve::is_even(eve::inc(tz)));
};
