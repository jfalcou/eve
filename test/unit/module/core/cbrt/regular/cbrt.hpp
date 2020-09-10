//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::cbrt return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cbrt(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cbrt behavior", EVE_TYPE)
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cbrt(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::Minf<T>()), eve::Minf<T>());
  }

  TTS_ULP_EQUAL(eve::cbrt(T(1))   , T( 1), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(T(-1))  , T(-1), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(T(8))   , T( 2), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(T(-8))  , T(-2), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(T(0))   , T( 0), 0  );
  TTS_ULP_EQUAL(eve::cbrt(T(-0.)) , T( 0), 0.5);

  TTS_EXPECT( all(is_negative(eve::cbrt(T(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::cbrt(T(0)))  ) );
}
