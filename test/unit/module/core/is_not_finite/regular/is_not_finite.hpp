//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_not_finite return type")
{
  TTS_EXPR_IS(eve::is_not_finite(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_not_finite behavior")
{
  TTS_EQUAL(eve::is_not_finite(Type(0)), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_finite(Type(2)), eve::False<Type>() );

  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_infinites)
  {
    TTS_EQUAL(eve::is_not_finite(eve::Inf<Type>())  , eve::True<Type>());
    TTS_EQUAL(eve::is_not_finite(eve::Minf<Type>()) , eve::True<Type>());
  }

  if constexpr(std::is_floating_point_v<Value> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_not_finite(eve::Nan<Type>()), eve::True<Type>());
  }
}
