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
    TTS_IEEE_EQUAL(eve::log1p(eve::Inf<T>())  , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::log1p(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::log1p(eve::Mone<T>()) , eve::Minf<T>());
    TTS_IEEE_EQUAL(eve::log1p(T( 0 ))         , T( 0 )        );
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::Mindenormal<T>()), T(std::log1p(eve::Mindenormal<v_t>())));
  }

  auto epsi = eve::Eps<T>();

  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(1))                    , eve::Log_2<T>()         , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(0))                    , T(0)                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(eve::Smallestposval<T>()), eve::Smallestposval<T>(), 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
}
