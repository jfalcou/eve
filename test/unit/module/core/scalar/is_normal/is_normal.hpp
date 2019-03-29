//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NORMAL_HPP
#define IS_NORMAL_HPP

#include <eve/function/scalar/is_normal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>  
#include <eve/as_logical.hpp>

TTS_CASE("Check is_normal return type")
{
  TTS_EXPR_IS(eve::is_normal(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_normal behavior")
{
  TTS_EQUAL(eve::is_normal(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_normal(Type{2}), eve::True<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL ( eve::is_normal(eve::Smallestposval<Type>()/2)
              , eve::logical<Type>(!eve::platform::supports_denormals)
              );
    TTS_EQUAL(eve::is_normal(eve::Inf<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_normal(eve::Nan<Type>()), eve::False<Type>());
  }
  
}

#endif
