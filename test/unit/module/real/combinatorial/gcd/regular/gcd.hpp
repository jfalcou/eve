//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gcd.hpp>
#include <eve/platform.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/value.hpp>

TTS_CASE_TPL("Check eve::anp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gcd(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::gcd behavior", EVE_TYPE)
{

 auto eve__gcd =  [](auto n, auto p) { return eve::gcd(n, p); };

  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(eve__gcd(T(2), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__gcd(T(2), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__gcd(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__gcd(T(3.3), T(2)),  eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::to_nearest(eve::gcd)(T(3.6), T(2)),  T(2), 0);
    TTS_ULP_EQUAL(eve::downward(eve::gcd)(T(3.6), T(2)), T(1), 0);
  }

  TTS_ULP_EQUAL(eve__gcd(T(10), T(5)), T(5), 0);
  TTS_ULP_EQUAL(eve__gcd(T(6), T(2)), T(2), 0);
  TTS_ULP_EQUAL(eve__gcd(T(36), T(45)), T(9), 0);
  TTS_ULP_EQUAL(eve__gcd(T(1), T(0)), T(1), 0);
  TTS_ULP_EQUAL(eve__gcd(T(0), T(0)), T(0), 0);
  TTS_ULP_EQUAL(eve__gcd(T(0), T(1)), T(1), 0);
}
