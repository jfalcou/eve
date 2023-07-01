//==================================================================================================
/**
  EVE - Logressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/detail/meta.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/quaternion.hpp>
#include <boost/math/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of log on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using e_t = typename T::value_type;
  using eq_t = eve::quaternion<e_t>;
  for(size_t i = 0; i < a1.size(); ++i)
  {
    auto z  = eq_t(a0[i],a1[i],a2[i],a3[i]);
    auto lz = eve::log(z); ;
    TTS_RELATIVE_EQUAL(eve::exp(lz), z, 0.001);
  }
};

// TTS_CASE_WITH( "Check behavior of log on wide"
//         , eve::test::simd::ieee_reals
//              , tts::generate( tts::randoms(-10, 10)
//                             , tts::randoms(-10, 10)
//                             , tts::randoms(-10, 10)
//                             , tts::randoms(-10, 10)
//                             )
//         )
//   <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
// {
//   using e_t = eve::element_type_t<T>;
//   using z_t = eve::as_quaternion_t<T>;
//   auto z = z_t{a0,a1,a2,a3};
//   z_t lz = eve::log(z);

//   TTS_RELATIVE_EQUAL(eve::exp(lz), z, 0.001);
// };
