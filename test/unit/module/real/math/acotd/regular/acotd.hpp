//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acotd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::acotd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acotd(T(0)), T);
}

TTS_CASE_TPL("Check eve::acotd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::inf(eve::as<T>()))  , T(0), 0);
    TTS_ULP_EQUAL(eve::acotd(eve::minf(eve::as<T>())) , T(0), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve::acotd(T( 0.5)), T( 63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(T(-0.5)), T(-63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(T(-1. )), T(-45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(T( 1. )), T( 45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(T( 0. )), T( 90)               , 0.5 );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<T>()));
  TTS_ULP_EQUAL(eve::acotd(T(-0.))      ,  T(-90)                             , 0.5);
  TTS_ULP_EQUAL(eve::acotd(inv_smallest), eve::radindeg(eve::smallestposval(eve::as<T>())), 0.5);
}
