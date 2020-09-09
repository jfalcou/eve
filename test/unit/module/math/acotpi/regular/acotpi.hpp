//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acotpi.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>

#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::acotpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acotpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::acotpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::Inf<T>()),  T(0), 0);
    TTS_ULP_EQUAL(eve::acotpi(eve::Minf<T>()), T(0), 0);
  }

  TTS_ULP_EQUAL(eve::acotpi(T( 0.5)) , eve::radinpi(T(1.107148717794090e+00)) , 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(T(-0.5)) , eve::radinpi(T(-1.107148717794090e+00)), 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(T(-1. )) , T(-0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(T( 1. )) , T( 0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(T( 0. )) , T( 0.5 )                               , 0.5 );

  auto inv_smallest = eve::rec(eve::Smallestposval<T>());
  TTS_ULP_EQUAL(eve::acotpi(T(-0.))       ,  T(-0.5)                              , 0.5);
  TTS_ULP_EQUAL(eve::acotpi(inv_smallest) , eve::radinpi(eve::Smallestposval<T>()), 0.5);
}
