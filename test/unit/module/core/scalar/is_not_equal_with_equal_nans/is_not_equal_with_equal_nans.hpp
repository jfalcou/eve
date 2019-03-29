//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP
#define IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP

#include <eve/function/scalar/is_not_equal_with_equal_nans.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE( "Check is_not_equal_with_equal_nans return type" )
{
  TTS_EXPR_IS(eve::is_not_equal_with_equal_nans(Type(), Type()) ,  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_equal_with_equal_nans behavior")
{
  TTS_EQUAL(eve::is_not_equal_with_equal_nans(Type(1),Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_not_equal_with_equal_nans(Type(3),Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_equal_with_equal_nans(eve::Nan<Type>(), eve::Nan<Type>()), eve::False<Type>());
}

#endif
