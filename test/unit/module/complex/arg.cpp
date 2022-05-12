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
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(eve::valmin, eve::valmax))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_EQUAL( eve::arg(eve::complex<e_t>(e, f)), eve::atan2(f, e) );
    }
  }
};

EVE_TEST( "Check behavior of arg on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(eve::valmin, eve::valmax))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;

  TTS_EQUAL( eve::arg(z_t{a0,a1}), eve::atan2(a1,a0) );
};
