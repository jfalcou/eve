//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::saturated_(eve::add)(Type(), Type()), (Type));
}

TTS_CASE("Check eve::saturated_(eve::add) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::add)(Type{0}, Type{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(Type{1}, Type{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(Type{2}, Type{2}), (Type)(4));

  TTS_EQUAL(eve::saturated_(eve::add)(Value{0}, Type{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(Value{1}, Type{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(Value{2}, Type{2}), (Type)(4));

  TTS_EQUAL(eve::saturated_(eve::add)(Type{0}, Value{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::add)(Type{1}, Value{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::add)(Type{2}, Value{2}), (Type)(4));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<Type>(),eve::One<Type>())),
                    (eve::Valmax<Type>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<Value>(),eve::One<Type>())),
                    (eve::Valmax<Type>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmax<Type>(),eve::One<Value>())),
                    (eve::Valmax<Type>())
                  );

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<Type>(),eve::Mone<Type>())),
                      (eve::Valmin<Type>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<Value>(),eve::Mone<Type>())),
                      (eve::Valmin<Type>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::add)(eve::Valmin<Type>(),eve::Mone<Value>())),
                      (eve::Valmin<Type>())
                    );

      TTS_EQUAL(eve::saturated_(eve::add)(Type(-1), Type(1)),  (Type)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(Type(-2), Type(-6)), (Type)(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(Value(-1), Type(1)),  (Type)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(Value(-2), Type(-6)), (Type)(-8));

      TTS_EQUAL(eve::saturated_(eve::add)(Type(-1), Value(1)),  (Type)(0));
      TTS_EQUAL(eve::saturated_(eve::add)(Type(-2), Value(-6)), (Type)(-8));
    }
  }
}

