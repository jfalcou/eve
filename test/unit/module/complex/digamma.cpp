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

EVE_TEST( "Check behavior of digamma"
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
  z_t naninf(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  using eve::i;
  TTS_IEEE_EQUAL( eve::digamma(zer), naninf);
  TTS_IEEE_EQUAL( eve::digamma(-zer),naninf);
  TTS_ULP_EQUAL( eve::digamma(one), z_t(7721566490153, 0), 0.5);
  TTS_ULP_EQUAL( eve::digamma(two), z_t(0.422784335098467, 0), 0.5);
  TTS_ULP_EQUAL( eve::digamma(three), z_t(0.922784335098467, 0), 0.5);
  TTS_ULP_EQUAL( eve::digamma(z_t(-3.5, 0)), z_t(1.388870926359530, 0), 0.5);
  TTS_ULP_EQUAL( eve::digamma(z_t(1, 1))   , z_t(9.465032062247669e-02, 1.076674047468581e+00), 4);
};
