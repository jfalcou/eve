//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nez.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_nez return type")
{
  TTS_EXPR_IS(eve::is_nez(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_nez behavior")
{
  TTS_EQUAL(eve::is_nez(Type(0)), eve::False<Type>() );
  TTS_EQUAL(eve::is_nez(Type(2)), eve::True<Type>());

  if constexpr( std::is_floating_point_v<Value> )
  {
    TTS_EQUAL(eve::is_nez(eve::Mzero<Type>()), eve::False<Type>() );
  }
}
