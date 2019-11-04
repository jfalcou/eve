//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::sub) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::sub)(Type(), Type()), (Type));
}

TTS_CASE("Check eve::saturated_(eve::sub) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{0}, Type{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{3}, Type{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{6}, Type{2}), (Type)(4));

  TTS_EQUAL(eve::saturated_(eve::sub)(Value{0}, Type{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(Value{3}, Type{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(Value{6}, Type{2}), (Type)(4));

  TTS_EQUAL(eve::saturated_(eve::sub)(Type{0}, Value{0}), (Type)(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{3}, Value{1}), (Type)(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(Type{6}, Value{2}), (Type)(4));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmin<Type>(),eve::One<Type>())),
                    (eve::Valmin<Type>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmin<Value>(),eve::One<Type>())),
                    (eve::Valmin<Type>())
                  );
    TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmin<Type>(),eve::One<Value>())),
                    (eve::Valmin<Type>())
                  );

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<Type>(),eve::Mone<Type>())),
                      (eve::Valmax<Type>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<Value>(),eve::Mone<Type>())),
                      (eve::Valmax<Type>())
                    );

      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<Type>(),eve::Mone<Value>())),
                      (eve::Valmax<Type>())
                    );

      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-1), Type(1)),  (Type)(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-2), Type(-6)), (Type)(4));

      TTS_EQUAL(eve::saturated_(eve::sub)(Value(-1), Type(1)),  (Type)(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(Value(-2), Type(-6)), (Type)(4));

      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-1), Value(1)),  (Type)(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(Type(-2), Value(-6)), (Type)(4));
    }
  }
}

