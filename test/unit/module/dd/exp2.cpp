//==================================================================================================
/**
  EVE - Exp2ressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of exp2 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using dd_t= eve::dd<e_t>;
  auto thresh = 2*eve::high(eve::eps(eve::as<eve::dd<e_t>>()));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto x = dd_t(e, f);
      TTS_EXPECT ( (abs(tts::uptype(eve::exp2(eve::dd<e_t>(e, f)))- exp2(tts::uptype(x))))/tts::uptype(eve::exp2(x)) < thresh);
    }
      TTS_EQUAL(eve::exp2(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()));
      TTS_EQUAL(eve::exp2(eve::minf(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()));
      TTS_EXPECT(eve::is_nan(eve::exp2(eve::nan(eve::as<dd_t>()))));
  }
};

TTS_CASE_WITH( "Check behavior of exp2 on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::exp2, z));
  TTS_EQUAL ( eve::exp2(z), az);
};
