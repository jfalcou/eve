//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_not_real.hpp>
#include <eve/traits/as_logical.hpp>

TTS_CASE_TPL("Check is_not_real return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_real(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_real behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_real(T{0}), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_not_real(T{2}), eve::false_(eve::as<T>()));
}
