//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH ( "Check behavior of dec on scalar"
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
      TTS_ULP_EQUAL( eve::dec(a), c_t(eve::dec(e), f), 2);
    }
  }
};

TTS_CASE_WITH ( "Check behavior of dec on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(0, 100), tts::randoms(-10, 10))
              )
  <typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  z_t z(a0, a1);
  TTS_ULP_EQUAL( eve::dec(z), z_t(eve::dec(a0), a1), 2);
};
