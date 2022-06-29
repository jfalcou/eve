//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of is_finite on scalar"
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
      TTS_EQUAL( eve::is_finite(eve::complex<e_t>(e, f)), (eve::is_finite(e) && eve::is_finite(f)) );
    }
  }
};

TTS_CASE_WITH( "Check behavior of is_finite on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(eve::valmin, eve::valmax)
                             , tts::randoms(eve::valmin, eve::valmax))
        )
  <typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;

  auto test1 = eve::is_finite(z_t{a0,a1});
  auto test2 = eve::is_finite(a0) && eve::is_finite(a1);
  std::cout << test1 << "   " << test2 << std::endl;
  TTS_EQUAL( eve::is_finite(z_t{a0,a1}), (eve::is_finite(a0) && eve::is_finite(a1)) );
};
