//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
    TTS_ULP_EQUAL(eve::acotpi(eve::inf(eve::as<T>())),  T(0), 0);
    TTS_ULP_EQUAL(eve::acotpi(eve::minf(eve::as<T>())), T(0), 0);
  }

  TTS_ULP_EQUAL(eve::acotpi(T( 0.5)) , eve::radinpi(T(1.107148717794090e+00)) , 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(T(-0.5)) , eve::radinpi(T(-1.107148717794090e+00)), 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(T(-1. )) , T(-0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(T( 1. )) , T( 0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(T( 0. )) , T( 0.5 )                               , 0.5 );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<T>()));
  TTS_ULP_EQUAL(eve::acotpi(T(-0.))       ,  T(-0.5)                              , 0.5);
  TTS_ULP_EQUAL(eve::acotpi(inv_smallest) , eve::radinpi(eve::smallestposval(eve::as<T>())), 0.5);
}
