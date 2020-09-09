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
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::asech return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asech(T(0)), T);
}

TTS_CASE_TPL("Check eve::asech behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asech(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asech(eve::Inf<T>()) , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::asech(eve::Minf<T>()) , eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve::asech(T( 2))   ,  eve::nan(eve::as<T>())        , 0   );
  TTS_ULP_EQUAL(eve::asech(T(-2))   ,  eve::nan(eve::as<T>())        , 0   );
  TTS_ULP_EQUAL(eve::asech(T( 1. )) ,  T( 0 )               , 0   );
  TTS_ULP_EQUAL(eve::asech(T( 0.5 )),  T(std::acosh(v_t(2))), 0.5 );
}
