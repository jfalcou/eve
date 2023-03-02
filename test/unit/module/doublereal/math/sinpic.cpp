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


TTS_CASE_WITH( "Check behavior of sinpic on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-100, 100)
                              , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  auto pi = bm::atan(tts::uptype(eve::one(eve::as<dd_t>())))*4;
  auto ep = 4096.0*eve::high(eve::eps(eve::as<dd_t>()));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto bms = bm::sin(tts::uptype(z)*pi)/(tts::uptype(z)*pi);
      auto sf  = eve::sinpic(z);
      auto zz = tts::uptype(sf);
      auto diff = bms-zz;
     TTS_LESS_EQUAL(eve::abs(double(diff)), ep);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sinpic on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::sinpic, z));
  auto cz = eve::sinpic(z);
  TTS_ULP_EQUAL(cz, az, 10000);

};
