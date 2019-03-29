//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_UNORDERED_HPP
#define IS_UNORDERED_HPP

#include <eve/function/scalar/is_unordered.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp> 
#include <type_traits>

TTS_CASE( "Check is_unordered return type" )
{
  TTS_EXPR_IS(eve::is_unordered(Type(), Type()) ,  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_unordered behavior")
{
  TTS_EQUAL(eve::is_unordered(Type(1),Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_unordered(Type(3),Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_unordered(Type(1),Type(3)), eve::False<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_unordered(eve::Nan<Type>(),Type(3)), eve::True<Type>());
    TTS_EQUAL(eve::is_unordered(Type(3), eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_unordered(eve::Nan<Type>(), eve::Nan<Type>()), eve::True<Type>());
  }
}

#endif
