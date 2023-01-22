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
#include <boost/math/constants/constants.hpp>

TTS_CASE_WITH( "Check behavior of log on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  auto thresh = 4*eve::high(eve::eps(eve::as<eve::dd<e_t>>()));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto x = dd_t(e, f);
      TTS_EXPECT ( (abs(tts::uptype(eve::log(eve::dd<e_t>(e, f)))- log(tts::uptype(x))))/tts::uptype(eve::log(x)) < thresh);
    }
  }
  TTS_EXPECT(eve::is_nan(eve::log(eve::mone(eve::as<dd_t>()))));
  TTS_EQUAL(eve::log(eve::zero(eve::as<dd_t>())), eve::minf(eve::as<dd_t>()));
  TTS_EQUAL(eve::log(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()));

};

TTS_CASE_WITH( "Check behavior of log on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::log, z));
  TTS_EQUAL ( eve::log(z), az);
};
