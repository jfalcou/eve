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

TTS_CASE_WITH( "Check behavior of oneminus on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using dd_t= eve::dd<e_t>;
  auto thresh = 2*eve::high(eve::eps(eve::as<eve::dd<e_t>>()));
 for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto x = dd_t(e, f);
      TTS_EXPECT ( abs(tts::uptype(eve::oneminus(eve::dd<e_t>(e, f)))-  (tts::uptype(eve::one(eve::as(x))-x)))/tts::uptype(eve::oneminus(x)) < thresh);
    }
  }
};

TTS_CASE_WITH( "Check behavior of oneminus on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto z = make_dd(a0,a1);
  if constexpr(sizeof(e_t) == 4)
  {
    TTS_EQUAL ( eve::to_double(eve::oneminus(z)), eve::oneminus(eve::to_double(z)));

    auto z = eve::dd<e_t>((1ll << 40)+12);
    TTS_EQUAL ( eve::to_double(eve::oneminus(z)), eve::oneminus(eve::to_double(z)));
  }
};
