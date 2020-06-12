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
#include <eve/constant/maxflint.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::big_(eve::tand) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::tand)(T()), (T));
}

TTS_CASE_TPL("Check eve::big_(eve::tand) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::tand)(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::tand)(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::tand)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  TTS_IEEE_EQUAL(eve::big_(eve::tand)(T( 0 )) , T(0) );
  TTS_IEEE_EQUAL(eve::big_(eve::tand)(T(-0.)) , T(0) );

  TTS_ULP_EQUAL(eve::big_(eve::tand)( T(  1)) , T(1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::big_(eve::tand)(-T(  1)) , T(-1.74550649282175857651288952197278243141015888398755e-2) , 3 );
  TTS_ULP_EQUAL(eve::big_(eve::tand)( T( 45)) , T(1)  , 3 );
  TTS_ULP_EQUAL(eve::big_(eve::tand)(-T( 45)) , T(-1) , 3 );
  TTS_ULP_EQUAL(eve::big_(eve::tand)( T(500)) , T(-0.83909963117728001176312729812318136468743428301234)   , 10 );
  TTS_ULP_EQUAL(eve::big_(eve::tand)(-T(500)) , T(0.83909963117728001176312729812318136468743428301234)    , 10 );
  auto z = eve::Maxflint<T>()*180;
  TTS_ULP_EQUAL(eve::big_(eve::tand)(z) , T(0) , 0.5);
}
