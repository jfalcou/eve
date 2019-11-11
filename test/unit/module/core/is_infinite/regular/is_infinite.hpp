//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_infinite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_infinite return type")
{
  TTS_EXPR_IS(eve::is_infinite(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_infinite behavior")
{
  TTS_EQUAL(eve::is_infinite(Type(0)), eve::False<Type>()  );
  TTS_EQUAL(eve::is_infinite(Type(2)), eve::False<Type>() );

  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_infinites)
  {
    TTS_EQUAL(eve::is_infinite(eve::Inf<Type>())  , eve::True<Type>());
    TTS_EQUAL(eve::is_infinite(eve::Minf<Type>()) , eve::True<Type>());
  }

  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_infinite(eve::Nan<Type>()), eve::False<Type>());
  }
}

