//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/function/all.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asinpi return type")
{
  TTS_EXPR_IS(eve::asinpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::asinpi behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asinpi(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asinpi(EVE_TYPE(2))          , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asinpi(EVE_TYPE(-2))         , (eve::Nan<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve::asinpi(EVE_TYPE( 0.5)) , (EVE_TYPE(1./6))  , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(EVE_TYPE(-0.5)) , (EVE_TYPE(-1./6)) , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(EVE_TYPE(-1. )) , (EVE_TYPE(-0.5))  , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(EVE_TYPE( 1. )) , (EVE_TYPE(0.5))   , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(EVE_TYPE( 0. )) , (EVE_TYPE(0))     , 0.5);

  TTS_ULP_EQUAL(eve::asinpi(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)), 0.5);

  TTS_EXPECT( all(is_negative(eve::asinpi(eve::Mzero<EVE_TYPE>()))) );
  TTS_EXPECT( all(is_positive(eve::asinpi(EVE_TYPE(0))))            );
}
