//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_eqz.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE("Check eve::is_eqz return type")
{
  TTS_EXPR_IS(eve::is_eqz(EVE_TYPE()), eve::logical<EVE_TYPE>);
}

TTS_CASE_TPL("Check eve::is_eqz behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_eqz(T(0)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::is_eqz(T(2)), eve::false_(eve::as<T>()));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::is_eqz(T(-0.)), eve::true_(eve::as<T>()) );
  }
}
