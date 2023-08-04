//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of real on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using e_t = typename T::value_type;
  using q_t = eve::quaternion<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    TTS_EQUAL( eve::real(q_t(a0[i],a1[i],a2[i],a3[i])), a0[i] );
    q_t c;
    eve::real(c) = a0[i];
    eve::ipart(c) = a1[i];
    eve::jpart(c) = a2[i];
    eve::kpart(c) = a3[i];
    TTS_EQUAL(q_t(a0[i],a1[i],a2[i],a3[i]), c );
  }
};

TTS_CASE_WITH( "Check behavior of real on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        , tts::randoms(eve::valmin, eve::valmax)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = eve::element_type_t<T>;
  using z_t = eve::wide<eve::quaternion<e_t>, eve::cardinal_t<T> >;

  TTS_EQUAL( eve::real(z_t(a0,a1,a2,a3)), a0 );
  z_t c;
  eve::real(c) = a0;
  eve::ipart(c) = a1;
  eve::jpart(c) = a2;
  eve::kpart(c) = a3;
  TTS_EQUAL(z_t(a0,a1,a2,a3), c );
};
