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
             , tts::generate ( tts::randoms(-0.5, 0.5)
                              , tts::randoms(-0.5, 0.5)
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
        std::cout << std::setprecision(20) << std::defaultfloat << "z " << z << std::endl;
        auto ac = tts::uptype(eve::acos(z));
        auto bc = bm::acos(tts::uptype(z));
        auto as = tts::uptype(eve::asin(z));
        auto bs = bm::asin(tts::uptype(z));
        std::cout << "z  "<< tts::uptype(z)  << std::endl;
    std::cout << "ac "<< ac << std::endl;
    std::cout << "bc "<< bc << std::endl;
    std::cout << "as "<< as << std::endl;
    std::cout << "bs "<< bs << std::endl;
        std::cout << "bm::abs " << bm::abs(tts::uptype(eve::acos(z))- bm::acos(tts::uptype(z))) << "? < " << 8*tts::uptype(eve::eps(eve::as(z))) << std::endl;
        TTS_EXPECT ( bm::abs(tts::uptype(eve::acos(z))- bm::acos(tts::uptype(z))) < 8*tts::uptype(eve::eps(eve::as(z))));
    }
  }
};

TTS_CASE_WITH( "Check behavior of acos on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-0.7, 0.7)
                             , tts::randoms(-0.3, 0.3)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::acos, z));
  auto cz = eve::acos(z);
  TTS_EQUAL ( cz, az);
};
