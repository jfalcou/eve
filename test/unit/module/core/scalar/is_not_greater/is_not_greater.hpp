//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_GREATER_HPP
#define IS_NOT_GREATER_HPP

#include <eve/function/scalar/is_not_greater.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE( "Check is_not_greater return type" )
{
  TTS_EXPR_IS(eve::is_not_greater(Type(), Type()) ,  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_greater behavior")
{
  TTS_EQUAL(eve::is_not_greater(Type(1),Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_greater(Type(3),Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_not_greater(Type(1),Type(3)), eve::True<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_not_greater(eve::Nan<Type>(),Type(3)), eve::True<Type>());
    TTS_EQUAL(eve::is_not_greater(Type(3), eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_not_greater(eve::Nan<Type>(),eve::Nan<Type>()), eve::True<Type>());
  }
      
}

#endif
