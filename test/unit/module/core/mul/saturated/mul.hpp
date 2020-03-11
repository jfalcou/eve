//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::mul) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::mul)(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check saturated_(eve::mul) behavior")
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
      TTS_EQUAL(saturated_(eve::mul)(tvmin       , (EVE_TYPE(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       , (EVE_TYPE(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)((EVE_TYPE(-1))  , (EVE_TYPE( 0))), EVE_TYPE(0));
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,      tvmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,      tvmin), tvmin);

      TTS_EQUAL(saturated_(eve::mul)(vmax       , (EVE_TYPE(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)(vmin       , (EVE_TYPE(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((EVE_VALUE(-1)), (EVE_TYPE( 0))), EVE_TYPE(0));
      TTS_EQUAL(saturated_(eve::mul)(vmax       ,      tvmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(vmax       ,      tvmin), tvmin);

      TTS_EQUAL(saturated_(eve::mul)(tvmax       , (EVE_VALUE(-2))), tvmin);
      TTS_EQUAL(saturated_(eve::mul)(tvmin       , (EVE_VALUE(-2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((EVE_TYPE(-1))  , (EVE_VALUE( 0))), EVE_TYPE(0));
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,        vmax), tvmax);
      TTS_EQUAL(saturated_(eve::mul)(tvmax       ,        vmin), tvmin);

    }
    else
    {
      TTS_EQUAL(saturated_(eve::mul)(tvmax    , (EVE_TYPE(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((EVE_TYPE(2)), tvmax)    , tvmax);

      TTS_EQUAL(saturated_(eve::mul)(vmax      , (EVE_TYPE(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((EVE_VALUE(2)), tvmax)    , tvmax);

      TTS_EQUAL(saturated_(eve::mul)(tvmax     , (EVE_VALUE(2))), tvmax);
      TTS_EQUAL(saturated_(eve::mul)((EVE_TYPE(2)) , vmax )     , tvmax);

    }
  }
  else
  {
    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE(12) , EVE_TYPE(4)), EVE_TYPE(48  ) );

    TTS_EQUAL(saturated_(eve::mul)(EVE_VALUE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_VALUE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_VALUE(12) , EVE_TYPE(4)), EVE_TYPE(48  ) );

    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE( 0) , EVE_VALUE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE( 1) , EVE_VALUE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated_(eve::mul)(EVE_TYPE(12) , EVE_VALUE(4)), EVE_TYPE(48  ) );
  }
}
