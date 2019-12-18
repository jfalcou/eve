//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/unary_minus.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>

TTS_CASE("Check eve::unary_minus return type")
{
  TTS_EXPR_IS(eve::unary_minus(Type(0)), (Type));
}

TTS_CASE("Check eve::unary_minus behavior")
{
  TTS_EQUAL(eve::unary_minus(Type( 1)) , static_cast<Type>(-1));
  TTS_EQUAL(eve::unary_minus(Type(-1)) , static_cast<Type>( 1));
  if (std::is_floating_point_v<Value>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::unary_minus(eve::Zero<Type>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::unary_minus(eve::Mzero<Type>())))); 
  }
  
}
