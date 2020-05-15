//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gamma.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::gamma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gamma(T(0)), T);
}

TTS_CASE_TPL("Check eve::gamma behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::gamma(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::gamma(eve::Inf<T>())  , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::gamma(eve::Minf<T>()) , eve::Nan<T>() );
  }

  TTS_ULP_EQUAL(eve::gamma(T(0.5)), T(std::tgamma(v_t(0.5))), 1. );
  TTS_ULP_EQUAL(eve::gamma(T(-35)), T(std::tgamma(v_t(-35))), 0.5);

  TTS_IEEE_EQUAL(eve::gamma(T( 0 )), eve::Inf<T>()  );
  TTS_IEEE_EQUAL(eve::gamma(T(-0.)), eve::Minf<T>() );
  TTS_IEEE_EQUAL(eve::gamma(T( 1 )), T(1)           );
  TTS_IEEE_EQUAL(eve::gamma(T( 2 )), T(1)           );
  TTS_IEEE_EQUAL(eve::gamma(T( 3 )), T(2)           );
  TTS_IEEE_EQUAL(eve::gamma(T( 5 )), T(24)          );
}
