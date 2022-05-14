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

EVE_TEST( "Check behavior of proj on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate(eve::test::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    TTS_EQUAL( eve::proj(e), eve::complex<e_t>(e, 0));
    TTS_EQUAL( eve::proj(eve::complex(e, e)), eve::complex(e,e) );
  }
};

EVE_TEST( "Check behavior of proj on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0 )
{
  using z_t = eve::as_complex_t<T>;
  TTS_EQUAL( eve::proj(a0)        , (z_t(a0, 0)) );
  TTS_EQUAL( eve::proj(z_t{a0,a0}), (z_t{a0,a0}) );
};
