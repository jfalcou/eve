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

EVE_TEST( "Check behavior of tgamma"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1000.0, +1000.0)
                              , eve::test::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& , T const&  )
{
  using e_t = typename T::value_type;
//  using z_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  z_t inf(eve::inf(eve::as<e_t>()), 0);
  z_t nan(eve::nan(eve::as<e_t>()), eve::nan(eve::as<e_t>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  TTS_IEEE_EQUAL( eve::tgamma(zer), inf );
  TTS_IEEE_EQUAL( eve::tgamma(-zer), -inf);
  TTS_EQUAL( eve::tgamma(one), one );
  TTS_EQUAL( eve::tgamma(two), one);
  TTS_ULP_EQUAL( eve::tgamma(three), two, 1);
  TTS_ULP_EQUAL( eve::tgamma(z_t( 3.5, 0)), z_t(3.323350970447843, 0), 2.5);
  TTS_ULP_EQUAL( eve::tgamma(z_t(-3.5, 0)), z_t(0.270088205852269, 0), 2.5);
  TTS_ULP_EQUAL( eve::tgamma(z_t(3.75, 0)), z_t(4.422988410460251, 0), 2.5);
  TTS_ULP_EQUAL( eve::tgamma(z_t(-3.75, 0)), z_t(0.267866128861417, 0), 4);
  TTS_ULP_EQUAL( eve::tgamma(z_t(4, 0))    , z_t(6, 0)                , 2.5);
  TTS_ULP_EQUAL( eve::tgamma(z_t(1, 1))   , z_t( 0.498015668118356, - 0.154949828301811), 4);
};
