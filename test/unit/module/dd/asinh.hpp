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
#include <boost/multiprecision/cpp_bin_float.hpp>


TTS_CASE_WITH( "Check behavior of abs on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-0.7, 0.7)
                              , tts::randoms(-0.3, 0.3)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
      std::cout << std::setprecision(20) << std::defaultfloat << "z " << z << std::endl;
      std::cout << bm::abs(tts::uptype(eve::asinh(z))- bm::asinh(tts::uptype(z))) << "? < " << tts::uptype(eve::eps(eve::as(z))) << std::endl;
      TTS_EXPECT ( bm::abs(tts::uptype(eve::asinh(z))- bm::asinh(tts::uptype(z))) < tts::uptype(eve::eps(eve::as(z))));
    }
  }
};

TTS_CASE_WITH( "Check behavior of asinh on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-0.7, 0.7)
                             , tts::randoms(-0.3, 0.3)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::asinh, z));
  auto cz = eve::asinh(z);
  TTS_EQUAL ( cz, az);
};
