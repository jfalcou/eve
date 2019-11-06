//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincosh.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/sinh.hpp>   
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>   
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <tuple>

TTS_CASE("Check eve::sincosh return type")
{
  TTS_EXPR_IS(eve::sincosh(Type(0)) , (std::pair<Type,Type>));
}

TTS_CASE("Check eve::eve::sincosh behavior")
{
  {
    auto [sh, ch ] = eve::sincosh(eve::Zero<Type>());
    TTS_ULP_EQUAL(sh  , Type(0), 0.5);
    TTS_ULP_EQUAL(ch ,  Type(1), 0.5);
    TTS_EXPECT(eve::all(eve::is_positive(sh))); 
  }
  {
    auto [sh, ch ] = eve::sincosh(eve::Mzero<Type>());
    TTS_ULP_EQUAL(sh  , Type(0), 0.5);
    TTS_ULP_EQUAL(ch ,  Type(1), 0.5);
    TTS_EXPECT((eve::all(eve::is_negative(sh)))); 
  }
  {
    auto [sh, ch ] = eve::sincosh(Type(1));
    TTS_ULP_EQUAL(sh  , eve::sinh(Type(1)), 0.5);
    TTS_ULP_EQUAL(ch ,  eve::cosh(Type(1)), 0.5);
  }
}
