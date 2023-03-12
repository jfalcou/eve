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

double fac = 1.0;
TTS_CASE_WITH( "Check behavior of cos on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-3.14/2, 3.14/2)
                              , tts::randoms(0, +0.0001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto sf  = eve::half_circle(eve::cos)(z);
      auto s   = tts::to_doublereal<e_t>((bm::cos)(tts::uptype(z)));  //dd_t(eve::cos(eve::high(z)));
      TTS_ULP_EQUAL(sf, s , 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of cos on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.544*20000, 1.54*20000)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    auto z = make_doublereal(a0,a1);
    auto az = decltype(z)(eve::detail::map(eve::half_circle(eve::cos), z));
                          auto cz = eve::half_circle(eve::cos)(z);
    TTS_ULP_EQUAL(cz, az, 0.5);
  }
};
