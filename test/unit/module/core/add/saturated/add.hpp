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

TTS_CASE_TPL("Check eve::saturated_(eve::add) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated_(eve::add)(T(), T()), T);
}

TTS_CASE_TPL("Check eve::saturated_(eve::add) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::saturated_(eve::add)(T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated_(eve::add)(T{1}, T{1}), T(2));
  TTS_EQUAL(eve::saturated_(eve::add)(T{2}, T{2}), T(4));

  TTS_EQUAL(eve::saturated_(eve::add)(v_t{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated_(eve::add)(v_t{1}, T{1}), T(2));
  TTS_EQUAL(eve::saturated_(eve::add)(v_t{2}, T{2}), T(4));

  TTS_EQUAL(eve::saturated_(eve::add)(T{0}, v_t{0}), T(0));
  TTS_EQUAL(eve::saturated_(eve::add)(T{1}, v_t{1}), T(2));
  TTS_EQUAL(eve::saturated_(eve::add)(T{2}, v_t{2}), T(4));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<T>(),eve::One<T>())),
                    (eve::Valmax<T>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<v_t>(),eve::One<T>())),
                    (eve::Valmax<T>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<T>(),eve::One<v_t>())),
                    (eve::Valmax<T>())
                  );

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<T>(),eve::Mone<T>())),
                      (eve::Valmin<T>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<v_t>(),eve::Mone<T>())),
                      (eve::Valmin<T>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<T>(),eve::Mone<v_t>())),
                      (eve::Valmin<T>())
                    );

      TTS_EQUAL(eve::saturated_(eve::add)(T(-1), T(1)),  T(0));
      TTS_EQUAL(eve::saturated_(eve::add)(T(-2), T(-6)), T(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(v_t(-1), T(1)),  T(0));
      TTS_EQUAL(eve::saturated_(eve::add)(v_t(-2), T(-6)), T(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(T(-1), v_t(1)),  T(0));
      TTS_EQUAL(eve::saturated_(eve::add)(T(-2), v_t(-6)), T(-8));
    }
  }
}

