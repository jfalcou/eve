//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <eve/module/doublereal/detail/pi_trigo.hpp>


TTS_CASE_WITH( "Check behavior of cos on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-0.49, 0.49)
                              , tts::randoms(0.01, +0.01)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  auto pi = bm::atan(tts::uptype(eve::one(eve::as<dd_t>())))*4;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto sf  = eve::half_circle(eve::cospi)(z);
      auto s   = tts::to_doublereal<e_t>((bm::cos)(tts::uptype(z)*pi));
      TTS_ULP_EQUAL(sf, s , 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of cos on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-0.24, 0.24)
                             , tts::randoms(-0.01, +0.01)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::half_circle(eve::cospi), z));
  auto cz = eve::half_circle(eve::cospi)(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
