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
#include <cmath>

TTS_CASE_WITH( "Check behavior of clamp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const&  a1, T const& a2)
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;

  for(auto sh : a2)
  {
    auto mi = doublereal_t(sh);
    auto ma = doublereal_t(sh)+10;
    for(auto f : a1)
    {
      for(auto e : a0)
      {
        auto z = doublereal_t(e, f);
        auto r =  eve::clamp(z, mi, ma);
        auto t =  (z >= ma) ? ma : (z <= mi ? mi : z);
        TTS_ULP_EQUAL(r, t, 0.5);
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of clamp on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)
                        )
        )
  <typename T>(T const& a0, T const& a1, T const& a2 )
{
  auto z = eve::make_doublereal(a0,a1);
  auto mi = eve::make_doublereal(a2, eve::zero(eve::as(a2)));
  auto ma = mi+10;
  auto t = eve::if_else(z >= ma, ma, eve::if_else(z <= mi, mi, z));
  TTS_ULP_EQUAL(eve::clamp(z, mi, ma), t, 0.5);
};
