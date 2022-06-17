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

EVE_TEST( "Check behavior of lgamma"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1000.0, +1000.0)
                              , eve::test::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& , T const&  )
{
//  using e_t = typename T::value_type;
//  using z_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using eve::i;
  T inf(eve::inf(eve::as<T>()));
  T nan(eve::nan(eve::as<T>()));
  z_t one(1, 0);
  z_t zer(0, 0);
  z_t two(2, 0);
  z_t three(3, 0);
  TTS_IEEE_EQUAL( eve::lgamma(zer), nan+i*nan );
  TTS_IEEE_EQUAL( eve::lgamma(-zer), nan-i*inf);
  TTS_EQUAL( eve::lgamma(one), zer );
  TTS_EQUAL( eve::lgamma(two), zer);
  TTS_ULP_EQUAL( eve::lgamma(three), eve::log(two), 0.5);
  TTS_ULP_EQUAL( eve::lgamma(z_t(-3.5, 0)), z_t(-1.309006684993043, 0), 0.5);
  TTS_ULP_EQUAL( eve::lgamma(z_t(1, 1))   , z_t( -0.650923199301856, -0.301640320467534), 4);
};
