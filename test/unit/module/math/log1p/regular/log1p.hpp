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
#include <cmath>

TTS_CASE("Check eve::log1p return type")
{
  TTS_EXPR_IS(eve::log1p(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::log1p behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::mone(eve::as<EVE_TYPE>())) , eve::minf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::log1p(EVE_TYPE( 0 ))         , EVE_TYPE( 0 )        );
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::mindenormal(eve::as<EVE_TYPE>())), EVE_TYPE(std::log1p(eve::mindenormal(eve::as<EVE_VALUE>()))));
  }

  auto epsi = eve::eps(eve::as<EVE_TYPE>());

  TTS_ULP_EQUAL(eve::log1p(epsi)        , epsi                            , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)        , epsi                            , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(EVE_TYPE(1)) , eve::log_2(eve::as<EVE_TYPE>()) , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(EVE_TYPE(0)) , EVE_TYPE(0)                     , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)        , epsi                            , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(eve::smallestposval(eve::as<EVE_TYPE>())), eve::smallestposval(eve::as<EVE_TYPE>()), 0.5 );
}
