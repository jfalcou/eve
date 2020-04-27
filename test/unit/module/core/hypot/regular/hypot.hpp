//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check hypot return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::hypot(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::hypot behavior", EVE_TYPE)
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<T>(), eve::Inf<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<T>(), eve::Nan<T>()), eve::Nan<T>(), 0);
  }

  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<T>(), (T(0)))          , eve::Inf<T>(), 0);
  TTS_ULP_EQUAL(eve::hypot((T(0))          , eve::Valmax<T>()), eve::Inf<T>(), 0);

  TTS_ULP_EQUAL(eve::hypot((T(-1)), (T(-1)))                  , eve::Sqrt_2<T>() , 0.5);
  TTS_ULP_EQUAL(eve::hypot((T( 1)), (T( 1)))                  , eve::Sqrt_2<T>() , 0.5);
  TTS_ULP_EQUAL(eve::hypot((T( 0)), (T( 0)))                  , (T(0))           , 0  );
  TTS_ULP_EQUAL(eve::hypot(eve::Sqrt_2<T>(), eve::Sqrt_2<T>()), T(2)             , 0.5);
}

TTS_CASE_TPL("Check 3 params eve::hypot behavior", EVE_TYPE)
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<T>(), eve::Inf<T>(), eve::Inf<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<T>(), eve::Nan<T>(), eve::Inf<T>()), eve::Nan<T>(), 0);
  }

  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<T>(), (T(0)),            (T(0)))          , eve::Inf<T>(), 0);
  TTS_ULP_EQUAL(eve::hypot((T(0))          , (eve::Valmax<T>()),  (T(0))),        eve::Inf<T>(), 0);

  TTS_ULP_EQUAL(eve::hypot((T(-1)), (T(-1)), (eve::Sqrt_2<T>()))                   , T(2) , 0.5);
  TTS_ULP_EQUAL(eve::hypot((T( 1)), (T( 1)), (eve::Sqrt_2<T>()))                   , T(2) , 0.5);
  TTS_ULP_EQUAL(eve::hypot((T( 0)), (T( 0)), (T( 0)))                             , (T(0)), 0  );
  TTS_ULP_EQUAL(eve::hypot((T( 1)), (T( 1)), (T( 1)))                             , T(std::sqrt(v_t(3))), 0.5);
}
