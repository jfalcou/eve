//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_not_real.hpp>
#include <eve/traits/as_logical.hpp>

TTS_CASE("Check is_not_real return type")
{
  TTS_EXPR_IS(eve::is_not_real(EVE_TYPE(0)), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::is_not_real behavior")
{
  TTS_EQUAL(eve::is_not_real(EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::is_not_real(EVE_TYPE(2)), eve::false_(eve::as<EVE_TYPE>()));
}
