//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asech.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::asech return type")
{
  TTS_EXPR_IS(eve::asech(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::asech behavior")
{

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asech(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asech(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::asech(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(eve::asech(EVE_TYPE( 2))   ,  eve::nan(eve::as<EVE_TYPE>())        , 0   );
  TTS_ULP_EQUAL(eve::asech(EVE_TYPE(-2))   ,  eve::nan(eve::as<EVE_TYPE>())        , 0   );
  TTS_ULP_EQUAL(eve::asech(EVE_TYPE( 1. )) ,  EVE_TYPE( 0 )               , 0   );
  TTS_ULP_EQUAL(eve::asech(EVE_TYPE( 0.5 )),  EVE_TYPE(std::acosh(EVE_VALUE(2))), 0.5 );
}
