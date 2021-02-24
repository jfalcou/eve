//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_flint.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_not_flint return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_flint(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_flint behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_flint(T(1)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_flint(T(2)), eve::false_(eve::as<T>()) );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_not_flint(eve::inf(eve::as<T>())), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::is_not_flint(eve::nan(eve::as<T>())), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::is_not_flint(T(1) / T(2)), eve::true_(eve::as<T>()));
  }
}
