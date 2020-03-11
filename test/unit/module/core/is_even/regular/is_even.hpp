//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_even.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_even return type")
{
  TTS_EXPR_IS(eve::is_even(EVE_TYPE(0)), (eve::logical<EVE_TYPE>));
}

TTS_CASE("Check eve::is_even behavior")
{
  TTS_EQUAL(eve::is_even(EVE_TYPE(1)), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_even(EVE_TYPE(2)), eve::True<EVE_TYPE>()  );

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_even(EVE_TYPE(0.5))         , eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::is_even(eve::Mzero<EVE_TYPE>()), eve::True<EVE_TYPE>() );
  }
}
