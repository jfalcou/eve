//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::div) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::div)(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check saturated_(eve::div) behavior")
{
  using eve::saturated_;

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    auto tvmax = eve::Valmax<EVE_TYPE>();
    auto tvmin = eve::Valmin<EVE_TYPE>();
    auto vmax = eve::Valmax<EVE_VALUE>();
    auto vmin = eve::Valmin<EVE_VALUE>();

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (EVE_TYPE(-1))), tvmin+(EVE_TYPE(1)));
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (EVE_TYPE(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(-1))  , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(-2) ) , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(1))   , (EVE_TYPE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(2))   , (EVE_TYPE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (EVE_TYPE( 0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(tvmax       , (EVE_VALUE(-1))), tvmin+(EVE_TYPE(1)));
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (EVE_VALUE(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(-1))  , (EVE_VALUE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(-2))  , (EVE_VALUE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(tvmin       , (EVE_VALUE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(1))   , (EVE_VALUE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(2))   , (EVE_VALUE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax       , (EVE_VALUE( 0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(vmax        , (EVE_TYPE(-1))), tvmin+(EVE_TYPE(1)));
      TTS_EQUAL(saturated_(eve::div)(vmin        , (EVE_TYPE(-1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(-1)) , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(-2)) , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)(vmin        , (EVE_TYPE( 0))), tvmin);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(1))  , (EVE_TYPE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(2))  , (EVE_TYPE( 0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(vmax        , (EVE_TYPE( 0))), tvmax);
     }
    else
    {
      TTS_EQUAL(saturated_(eve::div)(tvmax    , (EVE_TYPE(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(1)), (EVE_TYPE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(2)), (EVE_TYPE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax    , (EVE_TYPE(0))), tvmax);

      TTS_EQUAL(saturated_(eve::div)(vmax      , (EVE_TYPE(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(1)), (EVE_TYPE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_VALUE(2)), (EVE_TYPE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(vmax      , (EVE_TYPE(0))), tvmax);

     TTS_EQUAL(saturated_(eve::div)(tvmax     , (EVE_VALUE(1))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(1)) , (EVE_VALUE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)((EVE_TYPE(2)) , (EVE_VALUE(0))), tvmax);
      TTS_EQUAL(saturated_(eve::div)(tvmax     , (EVE_VALUE(0))), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE(12) , EVE_TYPE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 1) , EVE_TYPE(2)), EVE_TYPE(0.5) );

    TTS_EQUAL(saturated_(eve::div)(EVE_VALUE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_VALUE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_VALUE(12) , EVE_TYPE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_VALUE( 1) , EVE_TYPE(2)), EVE_TYPE(0.5) );

    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 0) , EVE_VALUE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 1) , EVE_VALUE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE(12) , EVE_VALUE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated_(eve::div)(EVE_TYPE( 1) , EVE_VALUE(2)), EVE_TYPE(0.5) );
  }
}
