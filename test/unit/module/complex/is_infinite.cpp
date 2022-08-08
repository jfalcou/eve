//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of is_infinite on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate(tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_EQUAL( eve::is_infinite(eve::complex<e_t>(e, f)), (eve::is_infinite(e) || eve::is_infinite(f)) );
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_infinite on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;

  TTS_EQUAL( eve::is_infinite(z_t{a0,a1}), (eve::is_infinite(a0) || eve::is_infinite(a1)) );
};
