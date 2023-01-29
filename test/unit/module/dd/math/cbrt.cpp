//==================================================================================================
/**
  EVE - Cbrtressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of cbrt on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-100, 100)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
      auto ac = eve::cbrt(z);
      auto bmbc = bm::cbrt(tts::uptype(z));
      eve::dd<e_t> bc(bmbc);
      TTS_ULP_EQUAL(bc, ac, 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of cbrt on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-100, 100)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::cbrt, z));
  auto cz = eve::cbrt(z);
  TTS_ULP_EQUAL(az, cz, 0.5);
};
