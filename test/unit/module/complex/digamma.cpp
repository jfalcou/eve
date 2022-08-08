//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of digamma"
        , eve::test::simd::ieee_reals
        ,tts::generate ( tts::randoms(-1000.0, +1000.0)
                              , tts::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& , T const&  )
{
  using e_t = typename T::value_type;
  using z_t = eve::complex<e_t>;
//  using z_t = eve::as_complex_t<e_t>;
  z_t inf(eve::inf(eve::as<e_t>()), 0);
  z_t nan(eve::nan(eve::as<e_t>()), eve::nan(eve::as<e_t>()));
  z_t naninf(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  using eve::i;
  TTS_IEEE_EQUAL( eve::digamma(zer), naninf);
  TTS_IEEE_EQUAL( eve::digamma(-zer),naninf);
  TTS_ULP_EQUAL( eve::real(eve::digamma(one)), e_t(-0.577215664901533), 25);
  TTS_ULP_EQUAL( eve::real(eve::digamma(two)), e_t(0.422784335098467), 25);
  TTS_ULP_EQUAL( eve::real(eve::digamma(three)), e_t(0.922784335098467), 25);
  TTS_ULP_EQUAL( eve::real(eve::digamma(z_t(-3.5, 0))), e_t(1.388870926359530), 25);
  TTS_ULP_EQUAL( eve::real(eve::digamma(z_t(-3.75, 0))), e_t(-1.692388598311321), 25);
  TTS_ULP_EQUAL( eve::digamma(z_t(1, 1))   , z_t(9.465032062247669e-02, 1.076674047468581e+00), 16);
  TTS_ULP_EQUAL( eve::digamma(z_t(-1, 1))   , z_t(0.594650320622477, 2.576674047468582), 4);
};
