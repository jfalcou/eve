//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::expm1 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expm1(T(0)), T);
}

TTS_CASE_TPL("Check eve::expm1 behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::Inf<T>()) , eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::expm1(eve::Minf<T>()), T(-1)        );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1(T( 0.)))));

  TTS_IEEE_EQUAL(eve::expm1(T(0))   , T(0) );
  TTS_IEEE_EQUAL(eve::expm1(T(-0.)) , T(0) );

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::expm1(T(1))    , T(std::expm1(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(T(-1))   ,T(std::expm1(v_t(-1))), 0.5);
}
