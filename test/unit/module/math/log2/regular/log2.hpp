//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::log2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log2(T(0)), T);
}

TTS_CASE_TPL("Check eve::log2 behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log2(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  );
    TTS_IEEE_EQUAL(eve::log2(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  );
    TTS_IEEE_EQUAL(eve::log2(eve::mone(eve::as<T>())) , eve::nan(eve::as<T>())  );
    TTS_IEEE_EQUAL(eve::log2(T( 0 ))         , eve::minf(eve::as<T>()) );
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log2(eve::mindenormal(eve::as<T>())), T(std::log2(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log2(T( 1)), T(0) );
  TTS_IEEE_EQUAL(eve::log2(T( 2)), T(1) );
  TTS_IEEE_EQUAL(eve::log2(T( 8)), T(3) );
  TTS_IEEE_EQUAL(eve::log2(T(64)), T(6) );
}
