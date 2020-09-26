//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::tanpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::tanpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::tanpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::tanpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::tanpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::tanpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_EXPECT( eve::all(eve::is_positive(eve::big(eve::tanpi)(T( 0 )))) );
  TTS_EXPECT( eve::all(eve::is_negative(eve::big(eve::tanpi)(T(-0.)))) );

  TTS_IEEE_EQUAL(eve::big(eve::tanpi)(T( 0 )), T(0) );
  TTS_IEEE_EQUAL(eve::big(eve::tanpi)(T(-0.)), T(0) );

  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(1)           ), T(0)         , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(-1)          ), T(0)         , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(22.5)        ), eve::nan(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)(-T(22.5)        ), eve::nan(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(100000.0)    ), T(0)         , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(-100000.0)   ), T(0)         , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(100000000.0) ), T(0)         , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::tanpi)( T(-100000000.0)), T(0)         , 0.5 );
  auto z = eve::maxflint(eve::as<T>())*10;
  TTS_ULP_EQUAL(eve::big(eve::tanpi)(z) , T(0) , 0.5);
}
