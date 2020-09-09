//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::pedantic_(eve::rsqrt) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::rsqrt)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::rsqrt) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(T(1)), T(1  ), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(T(4)), T(0.5), 0.5);

  if constexpr(eve::floating_value<T> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL((eve::pedantic_(eve::rsqrt)(eve::nan(eve::as<T>()))) , (eve::nan(eve::as<T>())));
    TTS_EQUAL(eve::pedantic_(eve::rsqrt)((T(0)))               , eve::Inf<T>());
  }

  using v_t = eve::element_type_t<T>;
  auto z = eve::Mindenormal<v_t>();

  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(eve::Mindenormal<T>())   , T(eve::rec(std::sqrt(z)))   , 2.0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::rsqrt)(2*eve::Mindenormal<T>()) , T(eve::rec(std::sqrt(2*z))) , 2.0);
}
