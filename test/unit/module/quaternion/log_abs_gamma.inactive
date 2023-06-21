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

TTS_CASE_WITH( "Check behavior of log_abs_gamma"
        , eve::test::simd::ieee_reals
        ,tts::generate ( tts::randoms(-1000.0, +1000.0)
                              , tts::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& , T const&  )
{
  using z_t = eve::as_complex_t<T>;
  using eve::i;
  T inf(eve::inf(eve::as<T>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  TTS_IEEE_EQUAL( eve::log_abs_gamma(zer), inf );
  TTS_EQUAL( eve::log_abs_gamma(one), T(0));
  TTS_EQUAL( eve::log_abs_gamma(two), T(0));
  TTS_ULP_EQUAL( eve::log_abs_gamma(three), eve::log(T(2)), 2.0);
  TTS_ULP_EQUAL( eve::log_abs_gamma(z_t(-3.5, 0)), eve::log_abs_gamma(T(-3.5)), 2.0);
  TTS_ULP_EQUAL( eve::log_abs_gamma(z_t(1, 1))   ,   eve::log_abs(z_t(0.49801566811835585, 0.1549498283018106)), 2.0);
};
