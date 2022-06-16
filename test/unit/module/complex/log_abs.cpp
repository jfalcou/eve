//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

EVE_TEST( "Check behavior of log_abs on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1000.0, +1000.0)
                              , eve::test::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
    for(auto f : a1)
    {
      TTS_ULP_EQUAL( eve::log_abs(eve::complex(e, f)), eve::log(eve::hypot(e,f)), 0.5);
    }
};

EVE_TEST( "Check behavior of log_abs on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1000.0, +1000.0)
                              , eve::test::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  TTS_ULP_EQUAL( eve::log_abs(z_t{a0,a1}), eve::log(eve::hypot(a0,a1)), 0.5);
  auto inf = eve::inf(eve::as<T>());
  auto nan = eve::nan(eve::as<T>());
  TTS_ULP_EQUAL( eve::log_abs(z_t{nan,inf}), inf, 0.5);
  TTS_ULP_EQUAL( eve::log_abs(z_t{inf, inf}), inf, 0.5);
  TTS_ULP_EQUAL( eve::log_abs(z_t{nan, nan}), nan, 0.5);

};
