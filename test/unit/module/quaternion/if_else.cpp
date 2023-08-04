//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of if_else on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate(tts::randoms(-100,+100))
        )
<typename T>(T const& a0 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    TTS_EQUAL( eve::if_else ( eve::is_odd(e)
                            , eve::quaternion<e_t>(0,-e, e, e)
                            , eve::quaternion<e_t>(0, e, e, e)
                            )
              , eve::quaternion<e_t>(0,eve::is_odd(e) ? -e : e, e, e)
              );
  }
};

TTS_CASE_WITH( "Check behavior of if_else on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-100,+100))
        )
<typename T>(T const& a0 )
{
  using e_t = typename T::value_type;
  using w_t = eve::wide<e_t, typename T::cardinal_type>;
  using z_t = eve::wide<eve::quaternion<e_t>, typename T::cardinal_type>;

  TTS_EQUAL( eve::if_else ( eve::is_odd(a0)
                          , z_t(0,-a0, a0, a0)
                          , z_t(0, a0, a0, a0)
                          )
            , z_t(0, eve::if_else(eve::is_odd(a0), -a0, a0), a0, a0)
            );

  TTS_EQUAL( eve::if_else ( eve::is_odd(a0)
                          , z_t(0,-a0, a0, a0)
                          , eve::quaternion<e_t>(-3, 1, 2, 4)
                          )
            , z_t ( eve::if_else(eve::is_odd(a0), w_t{0}, -3)
                  , eve::if_else(eve::is_odd(a0), -a0   ,  1)
                  , eve::if_else(eve::is_odd(a0), a0, 2)
                  , eve::if_else(eve::is_odd(a0), a0, 4)
                  )
            );
};
