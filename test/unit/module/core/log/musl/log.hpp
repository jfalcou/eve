//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::musl_(eve::log) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::musl_(eve::log)(T()), T);
}

TTS_CASE_TPL("Check eve::musl_(eve::log) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::musl_(eve::log)(eve::Inf<T>()) , eve::Inf<T>()  );
    TTS_IEEE_EQUAL(eve::musl_(eve::log)(eve::Nan<T>()) , eve::Nan<T>()  );
    TTS_IEEE_EQUAL(eve::musl_(eve::log)(eve::Mone<T>()), eve::Nan<T>()  );
    TTS_IEEE_EQUAL(eve::musl_(eve::log)(T(0))          , eve::Minf<T>() );
  }

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::musl_(eve::log)(eve::Mindenormal<T>()),T(std::log(eve::Mindenormal<v_t>())));
  }

  TTS_IEEE_EQUAL(eve::musl_(eve::log)(T( 1)), T( 0 )              );
  TTS_IEEE_EQUAL(eve::musl_(eve::log)(T( 2)), T(std::log(v_t(2))) );
  TTS_IEEE_EQUAL(eve::musl_(eve::log)(T( 8)), T(std::log(v_t(8))) );
  TTS_IEEE_EQUAL(eve::musl_(eve::log)(T(64)), T(std::log(v_t(64))));
}
