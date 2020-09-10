//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log10.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::log10 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log10(T()), T);
}

TTS_CASE_TPL("Check eve::log10 behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log10(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(eve::Mone<T>()) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log10(T( 0 ))         , eve::minf(eve::as<T>()));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log10(eve::mindenormal(eve::as<T>())), T(std::log10(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log10(T(1)      ), T(0) );
  TTS_IEEE_EQUAL(eve::log10(T(10)     ), T(1) );
  TTS_IEEE_EQUAL(eve::log10(T(1000)   ), T(3) );
  TTS_IEEE_EQUAL(eve::log10(T(1000000)), T(6) );
}
