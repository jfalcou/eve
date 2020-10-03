//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::tanpi return type")
{
  TTS_EXPR_IS(eve::tanpi(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::tanpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL((eve::tanpi)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::tanpi)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::tanpi)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::tanpi(EVE_TYPE(0))   , EVE_TYPE(0));
  TTS_IEEE_EQUAL(eve::tanpi(EVE_TYPE(-0.)) , EVE_TYPE(0));

  TTS_EXPECT( eve::all( eve::is_positive(eve::tanpi(EVE_TYPE( 0 ))) ));
  TTS_EXPECT( eve::all( eve::is_negative(eve::tanpi(EVE_TYPE(-0.))) ));

  TTS_ULP_EQUAL(eve::tanpi(EVE_TYPE(-1))           , EVE_TYPE(0)          , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi(EVE_TYPE(1))            , EVE_TYPE(0)          , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi( EVE_TYPE(22.5))        , eve::nan(eve::as<EVE_TYPE>()) , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi(-EVE_TYPE(22.5))        , eve::nan(eve::as<EVE_TYPE>()) , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi( EVE_TYPE(100000.0))    , EVE_TYPE(0)          , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi( EVE_TYPE(-100000.0))   , EVE_TYPE(0)          , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi( EVE_TYPE(100000000.0)) , EVE_TYPE(0)          , 0.5 );
  TTS_ULP_EQUAL(eve::tanpi( EVE_TYPE(-100000000.0)), EVE_TYPE(0)          , 0.5 );
}
