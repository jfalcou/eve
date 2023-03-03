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

TTS_CASE_WITH( "Check behavior of abs on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
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
      TTS_EQUAL ( tts::uptype(eve::abs(eve::doublereal<e_t>(e, f))), bm::abs(tts::uptype(eve::doublereal<e_t>(e, f))));
    }
  }
};

TTS_CASE_WITH( "Check behavior of abs on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::abs, z));
  TTS_EQUAL ( eve::abs(z), az);
//   std::cout << "sizeof(z) "<< sizeof(z)  << std::endl;
//   std::cout << "sizeof(element_type_t<decltype(z)>) " << sizeof(eve::element_type_t<decltype(z)>) << std::endl;
//   std::cout << eve::alignment_v<eve::element_type_t<decltype(z)>> << std::endl;
//   std::cout << eve::alignment_v<decltype(z)> << std::endl;
//   std::cout << eve::expected_cardinal_v<eve::element_type_t<decltype(z)>> << std::endl;
  std::cout << tts::typename_<decltype(z)> << std::endl;
  std::cout << alignof(decltype(z)) << std::endl;
  std::cout << tts::typename_<eve::element_type_t<decltype(z)>> << std::endl;
  std::cout << alignof(eve::element_type_t<decltype(z)>) << std::endl;

};
