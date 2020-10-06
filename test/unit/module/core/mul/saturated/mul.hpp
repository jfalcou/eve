//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/mul.hpp>

#include <type_traits>

TTS_CASE("Check saturated(eve::mul) return type")
{
  TTS_EXPR_IS(eve::saturated(eve::mul)(EVE_TYPE() , EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::mul)(EVE_VALUE(), EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::mul)(EVE_TYPE() , EVE_VALUE() ), EVE_TYPE);
}

TTS_CASE("Check saturated(eve::mul) behavior")
{
  if constexpr(eve::integral_value<EVE_VALUE>)
  {
    auto tvmax = eve::valmax(eve::as<EVE_TYPE>());
    auto vmax  = eve::valmax(eve::as<EVE_VALUE>());

    if constexpr(eve::signed_value<EVE_VALUE>)
    {
      auto tvmin = eve::valmin(eve::as<EVE_TYPE>());
      auto vmin = eve::valmin(eve::as<EVE_VALUE>());

      TTS_EQUAL(eve::saturated(eve::mul)(tvmin , EVE_TYPE(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , EVE_TYPE(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(-1) , EVE_TYPE( 0)), EVE_TYPE(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , tvmax), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , tvmin), tvmin);

      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , EVE_TYPE(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(vmin      , EVE_TYPE(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)((EVE_VALUE(-1)) , EVE_TYPE( 0)), EVE_TYPE(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , tvmax), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , tvmin), tvmin);

      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, EVE_VALUE(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmin, EVE_VALUE(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(-1), EVE_VALUE( 0)), EVE_TYPE(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, vmax   ), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, vmin   ), tvmin);
    }
    else
    {
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , EVE_TYPE(2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(2), tvmax ), tvmax);

      TTS_EQUAL(eve::saturated(eve::mul)(vmax  , EVE_TYPE(2)) , tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(EVE_VALUE(2), tvmax), tvmax);

      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, EVE_VALUE(2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(2) , vmax  ), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(12) , EVE_TYPE(4)), EVE_TYPE(48 ) );

    TTS_EQUAL(eve::saturated(eve::mul)(EVE_VALUE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_VALUE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_VALUE(12) , EVE_TYPE(4)), EVE_TYPE(48 ) );

    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE( 0) , EVE_VALUE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE( 1) , EVE_VALUE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(EVE_TYPE(12) , EVE_VALUE(4)), EVE_TYPE(48 ) );
  }
}
