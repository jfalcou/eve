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
  using e_t = typename T::value_type;
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

  TTS_ULP_EQUAL( eve::log_gamma(z_t( 3.5, 0)), z_t(1.2009736023470742, 0), 2.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-3.5, 0)), z_t(-1.309006684993042, 0), 2.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(3.75, 0)), z_t(1.48681557859341705, 0), 2.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-3.75, 0)), z_t(-1.317267942446363, 0), 4.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(4, 0))    , z_t(eve::log(T(6)), 0)                , 2.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(1, 1))   , z_t(-0.6509231993018563, -0.301640320467533197887531), 4.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-1,1))   , z_t(-0.9974967895818289, +2.054554169724811730959450), 4.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(1, -1))  , z_t(-0.6509231993018563, +0.301640320467533197887531), 4.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-1,-1))  , z_t(-0.997496789581828993, -2.054554169724811730959450), 4.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-1,0))   , z_t(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>())), 0.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(1, -2))  , z_t(-1.876078786430929341, -0.12964631630978831138370), 8.5);
  TTS_ULP_EQUAL( eve::log_gamma(z_t(-1,-2))  , z_t(-3.37394492320792483, -2.80759136089877543363209), 2.5);
};
