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
#include <boost/math/constants/constants.hpp>

TTS_CASE_WITH( "Check behavior of log1p on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
      auto ac = eve::log1p(z);
      auto bmbc = bm::log1p(tts::uptype(z));
      auto bc = tts::to_dd<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 2.5);
    }
  }
  TTS_ULP_EQUAL(eve::log1p(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log1p(eve::minf(eve::as<dd_t>())), eve::nan(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log1p(eve::zero(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log1p(eve::mzero(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log1p(eve::nan(eve::as<dd_t>())), eve::nan(eve::as<dd_t>()), 0.5);
};

TTS_CASE_WITH( "Check behavior of log1p on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::log1p, z));
  TTS_ULP_EQUAL ( eve::log1p(z), az, 0.5);
};
