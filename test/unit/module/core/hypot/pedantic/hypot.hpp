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

TTS_CASE("Check hypot return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(EVE_VALUE(0), EVE_TYPE(0)), (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(EVE_TYPE(0), EVE_VALUE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::hypot) behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Nan<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<EVE_VALUE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_VALUE>(), eve::Nan<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<EVE_TYPE>(), eve::Inf<EVE_VALUE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Nan<EVE_VALUE>()), eve::Inf<EVE_TYPE>(), 0);
  }

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_TYPE>(), (EVE_TYPE(0)))          , eve::Valmax<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(0))          , eve::Valmax<EVE_TYPE>()), eve::Valmax<EVE_TYPE>(), 0);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_VALUE>(), (EVE_TYPE(0)))          , eve::Valmax<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_VALUE(0))          , eve::Valmax<EVE_TYPE>()), eve::Valmax<EVE_TYPE>(), 0);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_TYPE>(), (EVE_VALUE(0)))          , eve::Valmax<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(0))          , eve::Valmax<EVE_VALUE>()), eve::Valmax<EVE_TYPE>(), 0);


  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_TYPE>()/2, eve::Valmax<EVE_TYPE>()/2), eve::Valmax<EVE_TYPE>()/eve::Sqrt_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_VALUE>()/2, eve::Valmax<EVE_TYPE>()/2), eve::Valmax<EVE_TYPE>()/eve::Sqrt_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_TYPE>()/2, eve::Valmax<EVE_VALUE>()/2), eve::Valmax<EVE_TYPE>()/eve::Sqrt_2<EVE_TYPE>(), 0.5);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_VALUE(-1)), (EVE_TYPE(-1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_VALUE( 1)), (EVE_TYPE( 1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_VALUE( 0)), (EVE_TYPE( 0)))                  , (EVE_TYPE(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<EVE_VALUE>(), eve::Sqrt_2<EVE_TYPE>()), EVE_TYPE(2)             , 0.5);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(-1)), (EVE_VALUE(-1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 1)), (EVE_VALUE( 1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 0)), (EVE_VALUE( 0)))                  , (EVE_TYPE(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<EVE_TYPE>(), eve::Sqrt_2<EVE_VALUE>()), EVE_TYPE(2)             , 0.5);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(-1)), (EVE_TYPE(-1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 1)), (EVE_TYPE( 1)))                  , eve::Sqrt_2<EVE_TYPE>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 0)), (EVE_TYPE( 0)))                  , (EVE_TYPE(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<EVE_TYPE>(), eve::Sqrt_2<EVE_TYPE>()), EVE_TYPE(2)             , 0.5);
}


TTS_CASE("Check pedantic_ 3 params eve::hypot behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_VALUE>(), eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_VALUE>(), eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_VALUE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_VALUE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_VALUE>(), eve::Inf<EVE_VALUE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_VALUE>(), eve::Inf<EVE_VALUE>()), eve::Inf<EVE_TYPE>(), 0);

  }

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<EVE_TYPE>(), (EVE_TYPE(0)),            (EVE_TYPE(0)))          , eve::Valmax<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(0))          , (eve::Valmax<EVE_TYPE>()),  (EVE_TYPE(0))),        eve::Valmax<EVE_TYPE>(), 0);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE(-1)), (EVE_TYPE(-1)), (eve::Sqrt_2<EVE_TYPE>()))                   , EVE_TYPE(2) , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 1)), (EVE_TYPE( 1)), (eve::Sqrt_2<EVE_TYPE>()))                   , EVE_TYPE(2) , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 0)), (EVE_TYPE( 0)), (EVE_TYPE( 0)))                             , (EVE_TYPE(0)), 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((EVE_TYPE( 1)), (EVE_TYPE( 1)), (EVE_TYPE( 1)))                             , EVE_TYPE(std::sqrt(EVE_VALUE(3))), 0.5);
}
