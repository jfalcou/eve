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

TTS_CASE_TPL("Check eve::saturated(eve::add) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::add)(T(), T()), T);
}

TTS_CASE_TPL("Check eve::saturated(eve::add) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::saturated(eve::add)(T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::add)(T{1}, T{1}), T(2));
  TTS_EQUAL(eve::saturated(eve::add)(T{2}, T{2}), T(4));

  TTS_EQUAL(eve::saturated(eve::add)(v_t{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{1}, T{1}), T(2));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{2}, T{2}), T(4));

  TTS_EQUAL(eve::saturated(eve::add)(T{0}, v_t{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::add)(T{1}, v_t{1}), T(2));
  TTS_EQUAL(eve::saturated(eve::add)(T{2}, v_t{2}), T(4));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<T>()),eve::one(eve::as<T>()))),
                    (eve::valmax(eve::as<T>()))
                  );
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<v_t>()),eve::one(eve::as<T>()))),
                    (eve::valmax(eve::as<T>()))
                  );
    TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmax(eve::as<T>()),eve::one(eve::as<v_t>()))),
                    (eve::valmax(eve::as<T>()))
                  );

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<T>()),eve::mone(eve::as<T>()))),
                      (eve::valmin(eve::as<T>()))
                    );

      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<v_t>()),eve::mone(eve::as<T>()))),
                      (eve::valmin(eve::as<T>()))
                    );

      TTS_EQUAL ( (eve::saturated(eve::add)(eve::valmin(eve::as<T>()),eve::mone(eve::as<v_t>()))),
                      (eve::valmin(eve::as<T>()))
                    );

      TTS_EQUAL(eve::saturated(eve::add)(T(-1), T(1)),  T(0));
      TTS_EQUAL(eve::saturated(eve::add)(T(-2), T(-6)), T(-8));

      TTS_EQUAL(eve::saturated(eve::add)(v_t(-1), T(1)),  T(0));
      TTS_EQUAL(eve::saturated(eve::add)(v_t(-2), T(-6)), T(-8));

      TTS_EQUAL(eve::saturated(eve::add)(T(-1), v_t(1)),  T(0));
      TTS_EQUAL(eve::saturated(eve::add)(T(-2), v_t(-6)), T(-8));
    }
  }
}

