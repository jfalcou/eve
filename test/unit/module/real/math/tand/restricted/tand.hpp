//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tand.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted(eve::tand) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::tand)(T()), (T));
}

TTS_CASE_TPL("Check eve::restricted(eve::tand) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tand)(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::tand)(T( 0 )) , T(0) );
  TTS_IEEE_EQUAL(eve::restricted(eve::tand)(T(-0.)) , T(0) );


  TTS_ULP_EQUAL(eve::restricted(eve::tand)( T(  1)) , T(1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)(-T(  1)) , T(-1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)( T( 45)) , T(1)  , 3 );
  TTS_ULP_EQUAL(eve::restricted(eve::tand)(-T( 45)) , T(-1) , 3 );
}
