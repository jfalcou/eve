//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::log1p return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log1p(T(0)), T);
}

TTS_CASE_TPL("Check eve::log1p behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::mone(eve::as<T>())) , eve::minf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::log1p(T( 0 ))         , T( 0 )        );
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::mindenormal(eve::as<T>())), T(std::log1p(eve::mindenormal(eve::as<v_t>()))));
  }

  auto epsi = eve::eps(eve::as<T>());

  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(1))                    , eve::log_2(eve::as<T>())         , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(0))                    , T(0)                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(eve::smallestposval(eve::as<T>())), eve::smallestposval(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
}
