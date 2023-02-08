//==================================================================================================
/**
  EVE - Expm1ressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>



TTS_CASE_WITH( "Check behavior of expm1 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
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
      auto z = dd_t(e, f);
      auto ac = eve::expm1(z);
      auto bmbc = bm::expm1(tts::uptype(z));
      auto bc = tts::to_dd<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 2.5);
    }
  }
  TTS_ULP_EQUAL(eve::expm1(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::minf(eve::as<dd_t>())), eve::mone(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::zero(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::mzero(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::nan(eve::as<dd_t>())), eve::nan(eve::as<dd_t>()), 0.5);

};

TTS_CASE_WITH( "Check behavior of expm1 on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::expm1, z));
  TTS_ULP_EQUAL ( eve::expm1(z), az, 2.5);
};
