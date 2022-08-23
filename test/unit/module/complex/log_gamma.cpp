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

TTS_CASE_WITH( "Check behavior of log_gamma"
        , eve::test::simd::ieee_reals
        ,tts::generate ( tts::randoms(-1000.0, +1000.0)
                              , tts::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& , T const&  )
{
//  using e_t = typename T::value_type;
//  using z_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using eve::i;
  T nan(eve::nan(eve::as<T>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  TTS_IEEE_EQUAL( eve::log_gamma(zer), nan+i*nan );
  TTS_EQUAL( eve::log_gamma(one), zer );
  TTS_EQUAL( eve::log_gamma(two), zer);
  TTS_ULP_EQUAL( eve::log_gamma(three), eve::log(two), 4);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-3.5, 0)), z_t(-1.309006684993043, 0), 4);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(1, 1))   , z_t( -0.650923199301856, -0.301640320467534), 4);
};
