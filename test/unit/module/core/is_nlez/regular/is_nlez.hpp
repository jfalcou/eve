//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nlez.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE("Check eve::is_nlez return type")
{
  TTS_EXPR_IS(eve::is_nlez(EVE_TYPE()), eve::logical<EVE_TYPE>);
}

TTS_CASE_TPL("Check eve::is_nlez behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_nlez(T(-1)), eve::false_(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_nlez(eve::nan(eve::as<T>())), eve::true_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_nlez(T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_nlez(T(3)), eve::true_(eve::as<T>()));
}
