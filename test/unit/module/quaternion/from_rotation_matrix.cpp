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

TTS_CASE_WITH ( "Check behavior of from_rotation_matrix on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate( tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const&  a3)
{
  using e_t =  typename T::value_type;
  using q_t = eve::quaternion<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto q = eve::sign(q_t(a0[i], a1[i], a2[i], a3[i]));
    auto m = eve::to_rotation_matrix(q, eve::Assume_normalized);
    auto q1 = eve::from_rotation_matrix(m);
    TTS_RELATIVE_EQUAL(q, q1, 0.0001);
  }
};
