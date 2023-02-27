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
             , tts::generate ( tts::randoms(-200, 200)
                              , tts::randoms(0.01, +0.01)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  auto pi = bm::atan(tts::uptype(eve::one(eve::as<dd_t>())))*4;
  if constexpr(sizeof(e_t) == 8)
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto sf  = eve::cospi(z);
      auto s   = tts::to_doublereal<e_t>((bm::cos)(tts::uptype(z)*pi));

      TTS_ULP_EQUAL(sf, s , 0.5) << (eve::abs(z) >= 1) << " sf " << tts::uptype(sf) << " s " << tts::uptype(s) << '\n';
    }
  }
};

// TTS_CASE_WITH( "Check behavior of cos on wide"
//              , eve::test::simd::ieee_reals
//              , tts::generate ( tts::randoms(-10000.0, 10000.0)
//                              , tts::randoms(-0.001, +0.001)
//                              )
//              )
//   <typename T>(T const& a0, T const& a1 )
// {
//   auto z = make_doublereal(a0,a1);
//   auto az = decltype(z)(eve::detail::map(eve::cospi, z));
//   auto cz = eve::cospi(z);
//   TTS_ULP_EQUAL(cz, az, 0.5);
// };
