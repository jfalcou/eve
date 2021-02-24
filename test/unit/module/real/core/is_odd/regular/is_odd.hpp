//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_odd.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check is_odd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_odd(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_odd behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_odd(T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_odd(T(2)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_odd(T(3)), eve::true_(eve::as<T>()) );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_odd(T( 0.5) ), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_odd(T(-0.)  ), eve::false_(eve::as<T>()));
  }
}
