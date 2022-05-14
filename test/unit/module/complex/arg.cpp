//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <eve/module/math.hpp>

EVE_TEST( "Check behavior of arg on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate(eve::test::randoms(-1000.0, 1000.0)
                             , eve::test::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
    for(auto f : a1)
      TTS_EQUAL( eve::arg(eve::complex(e, f)), eve::atan2(f, e) );
};

EVE_TEST( "Check behavior of arg on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1000.0, 1000.0)
                             , eve::test::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  TTS_EQUAL( eve::arg(z_t{a0,a1}), eve::atan2(a1,a0) );
};
