//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::acosh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acosh(T(0)), T);
}

TTS_CASE_TPL("Check eve::acosh behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acosh(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acosh(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()), 0);
  }

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::acosh(T( 0.5)) ,  eve::nan(eve::as<T>())  , 0   );
  TTS_ULP_EQUAL(eve::acosh(T(-0.5)) ,  eve::nan(eve::as<T>())  , 0   );
  TTS_ULP_EQUAL(eve::acosh(T( 1. )) ,  T( 0 ) , 0   );
  TTS_ULP_EQUAL(eve::acosh(T( 2. )) ,  T(std::acosh(v_t(2))), 0.5  );
}
