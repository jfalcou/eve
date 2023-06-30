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
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t =  typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    using eve::pedantic;
    for(int i = 0; i < 10; ++i)
    {
      {
        auto z = eve::sign(eve::quaternion(a0[i], a1[i], a2[i], a3[i]));
        auto [t1, t2, t3] = eve::to_euler(z, eve::_X, eve::_Z, eve::_X, false);
        auto q = eve::euler_to_quaternion(t1, t2, t3, eve::_X, eve::_Z, eve::_X, false);
        TTS_RELATIVE_EQUAL(q, z,  0.001);
      }
           {
        auto z = eve::sign(eve::quaternion(a0[i], a1[i], a2[i], a3[i]));
        auto [t1, t2, t3] = eve::to_euler(z, eve::_X, eve::_Z, eve::_X, true);
        auto q = eve::euler_to_quaternion(t1, t2, t3, eve::_X, eve::_Z, eve::_X, true);
        TTS_RELATIVE_EQUAL(q, z,  0.001);
      }
    }
  }
};

TTS_CASE_WITH ( "Check behavior of to_euler on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(0.25, +0.7)
                             , tts::randoms(0.25, +0.7)
                             , tts::randoms(0.25, +0.7)
                             )
              )
<typename T>(T const& a0, T const& a1, T const& a2 )
{
  using e_t =  typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    for(size_t i = 0; i < a0.size(); ++i)
    {
      {
        auto z = eve::euler_to_quaternion(a0[i], a1[i], a2[i], eve::_Z, eve::_X, eve::_Z, true);
        auto [t1, t2, t3] = eve::to_euler(z, eve::_Z, eve::_X, eve::_Z, true);
        TTS_RELATIVE_EQUAL(t1, a0[i], 0.001);
        TTS_RELATIVE_EQUAL(t2, a1[i], 0.001);
        TTS_RELATIVE_EQUAL(t3, a2[i], 0.001);
      }
      {
        auto z = eve::euler_to_quaternion(a0[i], a1[i], a2[i], eve::_Z, eve::_X, eve::_Z, false);
        auto [t1, t2, t3] = eve::to_euler(z, eve::_Z, eve::_X, eve::_Z, false);
        TTS_RELATIVE_EQUAL(t1, a0[i], 0.001);
        TTS_RELATIVE_EQUAL(t2, a1[i], 0.001);
        TTS_RELATIVE_EQUAL(t3, a2[i], 0.001);
      }
    }
  }
};
