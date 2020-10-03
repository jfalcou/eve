//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tand.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted(eve::tand) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::tand)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::restricted(eve::tand) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::tand)(EVE_TYPE( 0 )) , EVE_TYPE(0) );
  TTS_IEEE_EQUAL(eve::restricted(eve::tand)(EVE_TYPE(-0.)) , EVE_TYPE(0) );


  TTS_ULP_EQUAL(eve::restricted(eve::tand)( EVE_TYPE(  1)) , EVE_TYPE(1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)(-EVE_TYPE(  1)) , EVE_TYPE(-1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)( EVE_TYPE( 45)) , EVE_TYPE(1)  , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)(-EVE_TYPE( 45)) , EVE_TYPE(-1) , 3 );
}
