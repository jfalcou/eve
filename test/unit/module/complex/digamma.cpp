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
  TTS_ULP_EQUAL( eve::real(eve::digamma(one)), e_t(-0.577215664901532860606512090082402431042159335939923598805767234), 1.0);
  TTS_ULP_EQUAL( eve::real(eve::digamma(two)), e_t(0.4227843350984671393934879099175975689578406640600764011942327651), 2.0);
  TTS_ULP_EQUAL( eve::real(eve::digamma(three)), e_t(0.9227843350984671393934879099175975689578406640600764011942327651), 0.5);
  TTS_ULP_EQUAL( eve::real(eve::digamma(z_t(-3.5, 0))), e_t(1.3888709263595289015114046193821968137592213477205182739052536985), 0.5);
  TTS_ULP_EQUAL( eve::real(eve::digamma(z_t(-3.75, 0))), e_t(-1.692388598311330343154465211031748512432179503643307206720214624), 0.5);
  TTS_ULP_EQUAL( eve::digamma(z_t(1, 1))    , z_t(9.4650320622476947e-02, 1.076674047468581174e+00), 4);
  TTS_ULP_EQUAL( eve::digamma(z_t(-1, 1))   , z_t(0.594650320622477, 2.576674047468582), 4);
  TTS_ULP_EQUAL( eve::digamma(z_t(1, -1))   , z_t(9.4650320622476947e-02, -1.076674047468581174e+00), 4);
  TTS_ULP_EQUAL( eve::digamma(z_t(-1, -1))  , z_t(0.594650320622477, -2.576674047468582), 4);;
};
