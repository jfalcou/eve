//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>

TTS_CASE_TPL("Check eve::exponent return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exponent(T(0)), eve::as_integer_t<T>);
}

TTS_CASE_TPL("Check eve::exponent  behavior", EVE_TYPE)
{
  using r_t = eve::as_integer_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::exponent(eve::inf(eve::as<T>())) , r_t(0));
    TTS_EQUAL(eve::exponent(eve::minf(eve::as<T>())), r_t(0));
    TTS_EQUAL(eve::exponent(eve::nan(eve::as<T>())) , r_t(0));
  }

  TTS_EQUAL(eve::exponent(T(0   )), r_t(0));
  TTS_EQUAL(eve::exponent(T(1   )), r_t(0));
  TTS_EQUAL(eve::exponent(T(1.5 )), r_t(0));
  TTS_EQUAL(eve::exponent(T(2   )), r_t(1));
  TTS_EQUAL(eve::exponent(T(2.5 )), r_t(1));
  TTS_EQUAL(eve::exponent(T(4.5 )), r_t(2));
}
