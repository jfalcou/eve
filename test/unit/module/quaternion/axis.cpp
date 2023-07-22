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

TTS_CASE_WITH ( "Check behavior of axis on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = typename T::value_type;
  for(size_t i = 0; i <= a0.size(); ++i)
  {
    auto z = eve::sign(eve::quaternion(a0[i], a1[i], a2[i], a3[i]));
    auto q = eve::sign(eve::pure(z));
    std::array<e_t, 3> v{eve::ipart(q), eve::jpart(q), eve::kpart(q)};
    auto a =  eve::axis(z);

    for(int j=0; j < 3; ++j)
    {
      TTS_RELATIVE_EQUAL( a[j], v[j], 0.001);
    }
  }
};

TTS_CASE_WITH ( "Check behavior of axis on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_quaternion_t<T>;
  auto z = eve::sign(z_t(a0, a1, a2, a3));
  auto q = eve::sign(eve::pure(z));
  std::array<T, 3> v{eve::ipart(q), eve::jpart(q), eve::kpart(q)};
  auto a =  eve::axis(z);

  for(int i=0; i < 3; ++i)
  {
    TTS_RELATIVE_EQUAL( a[i], v[i], 0.001);
  }
};
