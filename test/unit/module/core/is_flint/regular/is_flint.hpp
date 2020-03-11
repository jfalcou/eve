//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_flint.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_flint return type")
{
  TTS_EXPR_IS(eve::is_flint(EVE_TYPE(0)), (eve::logical<EVE_TYPE>));
}

TTS_CASE("Check eve::is_flint behavior")
{
  TTS_EQUAL(eve::is_flint(EVE_TYPE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::is_flint(EVE_TYPE(2)), eve::True<EVE_TYPE>()  );

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_flint(EVE_TYPE(1) / EVE_TYPE(2)), eve::False<EVE_TYPE>());
  }
}
