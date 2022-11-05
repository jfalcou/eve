//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of is_nez on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  TTS_EQUAL( eve::is_nez(a), (eve::is_nez(a0) || eve::is_nez(a1)));
};
