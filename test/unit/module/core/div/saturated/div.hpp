//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check saturated(eve::div) return type")
{
  TTS_EXPR_IS(eve::saturated(eve::div)(  EVE_TYPE() ,   EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::div)(EVE_VALUE() ,   EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::saturated(eve::div)(  EVE_TYPE() , EVE_VALUE()), EVE_TYPE);
}

TTS_CASE("Check saturated(eve::div) behavior")
{
  using eve::saturated;

  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    auto tvmax  = eve::valmax(eve::as<EVE_TYPE>());
    auto vmax   = eve::valmax(eve::as<EVE_VALUE>());

    if constexpr(eve::signed_value<EVE_TYPE>)
    {
      auto vmin   = eve::valmin(eve::as<EVE_VALUE>());
      auto tvmin  = eve::valmin(eve::as<EVE_TYPE>());

      TTS_EQUAL(saturated(eve::div)(tvmax  , EVE_TYPE(-1) ), tvmin+(EVE_TYPE(1)) );
      TTS_EQUAL(saturated(eve::div)(tvmin  , EVE_TYPE(-1) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(-1)  , EVE_TYPE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(-2)  , EVE_TYPE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(tvmin  , EVE_TYPE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(1)   , EVE_TYPE( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(2)   , EVE_TYPE( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(tvmax  , EVE_TYPE( 0) ), tvmax        );

      TTS_EQUAL(saturated(eve::div)(tvmax  , EVE_VALUE(-1) ), tvmin+(EVE_TYPE(1)) );
      TTS_EQUAL(saturated(eve::div)(tvmin  , EVE_VALUE(-1) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(-1)  , EVE_VALUE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(-2)  , EVE_VALUE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(tvmin  , EVE_VALUE( 0) ), tvmin        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(1)   , EVE_VALUE( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(2)   , EVE_VALUE( 0) ), tvmax        );
      TTS_EQUAL(saturated(eve::div)(tvmax  , EVE_VALUE( 0) ), tvmax        );

      TTS_EQUAL(saturated(eve::div)(vmax   , EVE_TYPE(-1)), tvmin+(EVE_TYPE(1)));
      TTS_EQUAL(saturated(eve::div)(vmin   , EVE_TYPE(-1)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(-1), EVE_TYPE( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(-2), EVE_TYPE( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(vmin   , EVE_TYPE( 0)), tvmin       );
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(1) , EVE_TYPE( 0)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(2) , EVE_TYPE( 0)), tvmax       );
      TTS_EQUAL(saturated(eve::div)(vmax   , EVE_TYPE( 0)), tvmax       );
     }
    else
    {
      TTS_EQUAL(saturated(eve::div)(tvmax, EVE_TYPE(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(1) , EVE_TYPE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(2) , EVE_TYPE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(tvmax, EVE_TYPE(0)), tvmax);

      TTS_EQUAL(saturated(eve::div)(vmax   , EVE_TYPE(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(1) , EVE_TYPE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_VALUE(2) , EVE_TYPE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(vmax   , EVE_TYPE(0)), tvmax);

      TTS_EQUAL(saturated(eve::div)(tvmax, EVE_VALUE(1)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(1) , EVE_VALUE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(EVE_TYPE(2) , EVE_VALUE(0)), tvmax);
      TTS_EQUAL(saturated(eve::div)(tvmax, EVE_VALUE(0)), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE(12) , EVE_TYPE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 1) , EVE_TYPE(2)), EVE_TYPE(0.5) );

    TTS_EQUAL(saturated(eve::div)(EVE_VALUE( 0) , EVE_TYPE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_VALUE( 1) , EVE_TYPE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_VALUE(12) , EVE_TYPE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_VALUE( 1) , EVE_TYPE(2)), EVE_TYPE(0.5) );

    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 0) , EVE_VALUE(1)), EVE_TYPE(0  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 1) , EVE_VALUE(1)), EVE_TYPE(1  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE(12) , EVE_VALUE(4)), EVE_TYPE(3  ) );
    TTS_EQUAL(saturated(eve::div)(EVE_TYPE( 1) , EVE_VALUE(2)), EVE_TYPE(0.5) );
  }
}
