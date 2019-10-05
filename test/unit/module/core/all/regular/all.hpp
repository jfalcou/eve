//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ALL_HPP
#define ALL_HPP

#include <eve/function/all.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check all return type") {
  TTS_EXPR_IS(eve::all(eve::logical<Type>()), bool);
  TTS_EXPR_IS(eve::all(Type()), bool);
}

TTS_CASE("Check eve::all behavior")
{
  TTS_EQUAL(eve::all(Type{0}), false);
  TTS_EQUAL(eve::all(Type{1}), true);
  TTS_EQUAL(eve::all(Type{2}), true);
  if constexpr(std::is_floating_point_v<Type>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EQUAL(eve::all(eve::Nan<Type>()), true);
    }
    TTS_EQUAL(eve::all(eve::Mzero<Type>()), false);
  }
}

TTS_CASE("Check eve::all with logical entries behavior")
{
  TTS_EQUAL(eve::all(eve::True<Type>()), true);
  TTS_EQUAL(eve::all(eve::False<Type>()), false);
}

#endif
