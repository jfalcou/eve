//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated(eve::add) return type")
{
  TTS_EXPR_IS(eve::saturated(eve::add)(EVE_TYPE(), EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::saturated(eve::add) behavior")
{
  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(1), EVE_TYPE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(2), EVE_TYPE(2)), EVE_TYPE(4));

  TTS_EQUAL(eve::saturated(eve::add)(EVE_VALUE(0), EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_VALUE(1), EVE_TYPE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_VALUE(2), EVE_TYPE(2)), EVE_TYPE(4));

  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(0), EVE_VALUE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(1), EVE_VALUE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(2), EVE_VALUE(2)), EVE_TYPE(4));

  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<EVE_TYPE>()),eve::one(eve::as<EVE_TYPE>()))),
                    (eve::valmax(eve::as<EVE_TYPE>()))
                  );
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<EVE_VALUE>()),eve::one(eve::as<EVE_TYPE>()))),
                    (eve::valmax(eve::as<EVE_TYPE>()))
                  );
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<EVE_TYPE>()),eve::one(eve::as<EVE_VALUE>()))),
                    (eve::valmax(eve::as<EVE_TYPE>()))
                  );

    if constexpr(eve::signed_value<EVE_TYPE>)
    {
      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<EVE_TYPE>()),eve::mone(eve::as<EVE_TYPE>()))),
                      (eve::valmin(eve::as<EVE_TYPE>()))
                    );

      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<EVE_VALUE>()),eve::mone(eve::as<EVE_TYPE>()))),
                      (eve::valmin(eve::as<EVE_TYPE>()))
                    );

      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<EVE_TYPE>()),eve::mone(eve::as<EVE_VALUE>()))),
                      (eve::valmin(eve::as<EVE_TYPE>()))
                    );

      TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(-1), EVE_TYPE(1)),  EVE_TYPE(0));
      TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(-2), EVE_TYPE(-6)), EVE_TYPE(-8));

      TTS_EQUAL(eve::saturated(eve::add)(EVE_VALUE(-1), EVE_TYPE(1)),  EVE_TYPE(0));
      TTS_EQUAL(eve::saturated(eve::add)(EVE_VALUE(-2), EVE_TYPE(-6)), EVE_TYPE(-8));

      TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(-1), EVE_VALUE(1)),  EVE_TYPE(0));
      TTS_EQUAL(eve::saturated(eve::add)(EVE_TYPE(-2), EVE_VALUE(-6)), EVE_TYPE(-8));
    }
  }
}

