//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH ( "Check behavior of to_euler on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate( tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             )
              )
  <typename T>(T const& , T const& , T const& , T const&  )
{
  using e_t =  typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    using eve::pedantic;
    for(int i = 0; i < 1; ++i)
    {
      {
        auto sq = 0.707106781186548;
        auto z1 = eve::sign(eve::quaternion(1.0, 0.0, 0.0, 0.0));
        auto z2 = eve::sign(eve::quaternion(sq, 0.0, sq, 0.0));
//         auto z1 = eve::sign(eve::quaternion(a0[i], a1[i], a2[i], a3[i]));
//         auto z2 = eve::sign(eve::quaternion(a1[i], a0[i], a3[i], a2[i]));
        auto res = eve::slerp(z1, z2, 0.5);
        std::cout << res << std::endl;
        std::cout << eve::acos(eve::real(res)) << std::endl;

      }
    }
  }
};
