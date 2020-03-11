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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::add) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::add)(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::saturated_(eve::add) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{0}, EVE_TYPE{0}), (EVE_TYPE)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{1}, EVE_TYPE{1}), (EVE_TYPE)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{2}, EVE_TYPE{2}), (EVE_TYPE)(4));

  TTS_EQUAL(eve::saturated_(eve::add)(EVE_VALUE{0}, EVE_TYPE{0}), (EVE_TYPE)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_VALUE{1}, EVE_TYPE{1}), (EVE_TYPE)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_VALUE{2}, EVE_TYPE{2}), (EVE_TYPE)(4));

  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{0}, EVE_VALUE{0}), (EVE_TYPE)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{1}, EVE_VALUE{1}), (EVE_TYPE)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE{2}, EVE_VALUE{2}), (EVE_TYPE)(4));

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<EVE_TYPE>(),eve::One<EVE_TYPE>())),
                    (eve::Valmax<EVE_TYPE>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<EVE_VALUE>(),eve::One<EVE_TYPE>())),
                    (eve::Valmax<EVE_TYPE>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<EVE_TYPE>(),eve::One<EVE_VALUE>())),
                    (eve::Valmax<EVE_TYPE>())
                  );

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<EVE_TYPE>(),eve::Mone<EVE_TYPE>())),
                      (eve::Valmin<EVE_TYPE>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<EVE_VALUE>(),eve::Mone<EVE_TYPE>())),
                      (eve::Valmin<EVE_TYPE>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<EVE_TYPE>(),eve::Mone<EVE_VALUE>())),
                      (eve::Valmin<EVE_TYPE>())
                    );

      TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE(-1), EVE_TYPE(1)),  (EVE_TYPE)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE(-2), EVE_TYPE(-6)), (EVE_TYPE)(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(EVE_VALUE(-1), EVE_TYPE(1)),  (EVE_TYPE)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(EVE_VALUE(-2), EVE_TYPE(-6)), (EVE_TYPE)(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE(-1), EVE_VALUE(1)),  (EVE_TYPE)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(EVE_TYPE(-2), EVE_VALUE(-6)), (EVE_TYPE)(-8));
    }
  }
}

