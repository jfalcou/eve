//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>
//namespace bm =  boost::multiprecision;


TTS_CASE_WITH( "Check behavior of sqrt on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      if constexpr(sizeof(e_t) == 4)
      {
        TTS_ULP_EQUAL ( eve::to_double(eve::sqrt(eve::doublereal<e_t>(e, f))), eve::sqrt(eve::to_double(eve::doublereal<e_t>(e, f))), 10);
        std::cout << eve::to_double(eve::sqrt(eve::doublereal<e_t>(e, f)))- eve::sqrt(eve::to_double(eve::doublereal<e_t>(e, f))) << std::endl;
      }
//       else
//       {
//         TTS_EQUAL ( eve::to_float128(eve::sqrt(eve::doublereal<e_t>(e, f))), bm::sqrt(eve::to_float128(eve::doublereal<e_t>(e, f))));
//       }
    }
  }
};

TTS_CASE_WITH( "Check behavior of sqrt on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto z = make_doublereal(a0,a1);
  if constexpr(sizeof(e_t) == 4)
  {
    TTS_ULP_EQUAL ( eve::to_double(eve::sqrt(z)), eve::sqrt(eve::to_double(z)), 10);
  std::cout <<  eve::to_double(eve::sqrt(z))- eve::sqrt(eve::to_double(z))<< std::endl;
  }
};
