//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcnt.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::popcnt return type")
{
  TTS_EXPR_IS(eve::popcnt(Type()), std::make_unsigned_t<Type>);
}

TTS_CASE("Check eve::popcnt behavior")
{
  std::uint64_t full_pattern  = 0xFFFFFFFFFFFFFFFFULL;
  std::uint64_t pattern       = 0xAAAAAAAAAAAAAAAAULL;

  TTS_EQUAL(eve::popcnt(static_cast<Type>(0))            , 0ULL                );
  TTS_EQUAL(eve::popcnt(static_cast<Type>(full_pattern)) , 8ULL * sizeof(Type) );
  TTS_EQUAL(eve::popcnt(static_cast<Type>(pattern))      , 4ULL * sizeof(Type) );
}
