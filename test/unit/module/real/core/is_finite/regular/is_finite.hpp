//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_finite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::is_finite return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_finite(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_finite behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_finite(T(0)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_finite(T(2)), eve::true_(eve::as<T>()) );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_finite(eve::inf(eve::as<T>())) , eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_finite(eve::minf(eve::as<T>())), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_finite(eve::nan(eve::as<T>())) , eve::false_(eve::as<T>()));
  }
}
