//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH ( "Check behavior of oneminus on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(0, 100), tts::randoms(-10, 10))
              )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
   for(auto e : a0)
  {
    for(auto f : a1)
    {
      c_t a(e, f);
      TTS_ULP_EQUAL( eve::oneminus(a), c_t(eve::oneminus(e), -f), 2);
    }
  }
};

TTS_CASE_WITH ( "Check behavior of oneminus on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(0, 100), tts::randoms(-10, 10))
              )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  z_t z(a0, a1);
  TTS_ULP_EQUAL( eve::oneminus(z), z_t(eve::oneminus(a0), -a1), 2);
};
