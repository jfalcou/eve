//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>

TTS_CASE("Check eve::exponent return type")
{
  TTS_EXPR_IS(eve::exponent(EVE_TYPE(0)), eve::detail::as_integer_t<EVE_TYPE>);
}

TTS_CASE("Check eve::exponent  behavior")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::exponent(eve::inf(eve::as<EVE_TYPE>())) , r_t(0));
    TTS_EQUAL(eve::exponent(eve::minf(eve::as<EVE_TYPE>())), r_t(0));
    TTS_EQUAL(eve::exponent(eve::nan(eve::as<EVE_TYPE>())) , r_t(0));
  }

  TTS_EQUAL(eve::exponent(EVE_TYPE(0   )), r_t(0));
  TTS_EQUAL(eve::exponent(EVE_TYPE(1   )), r_t(0));
  TTS_EQUAL(eve::exponent(EVE_TYPE(1.5 )), r_t(0));
  TTS_EQUAL(eve::exponent(EVE_TYPE(2   )), r_t(1));
  TTS_EQUAL(eve::exponent(EVE_TYPE(2.5 )), r_t(1));
  TTS_EQUAL(eve::exponent(EVE_TYPE(4.5 )), r_t(2));
}

