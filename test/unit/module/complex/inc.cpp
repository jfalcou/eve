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

EVE_TEST( "Check behavior of inc on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate(eve::test::randoms(0, 100)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
   for(auto e : a0)
  {
    for(auto f : a1)
    {
      c_t a(e, f);
      TTS_ULP_EQUAL( eve::inc(a), c_t(eve::inc(e), f), 2);
    }
  }
};

EVE_TEST( "Check behavior of inc on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0, 100)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  z_t z(a0, a1);
  TTS_ULP_EQUAL( eve::inc(z), z_t(eve::inc(a0), a1), 2);
};
