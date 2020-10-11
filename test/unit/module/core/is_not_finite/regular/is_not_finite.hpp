//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_not_finite return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_finite(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_finite behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_finite(T(0)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_finite(T(2)), eve::false_(eve::as<T>()) );

  if constexpr(eve::floating_value<T> && eve::platform::supports_infinites)
  {
    TTS_EQUAL(eve::is_not_finite(eve::inf(eve::as<T>()))  , eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_not_finite(eve::minf(eve::as<T>())) , eve::true_(eve::as<T>()));
  }

  if constexpr(eve::floating_value<T> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_not_finite(eve::nan(eve::as<T>())), eve::true_(eve::as<T>()));
  }
}
