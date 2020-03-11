//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_not_finite return type")
{
  TTS_EXPR_IS(eve::is_not_finite(EVE_TYPE(0)), (eve::logical<EVE_TYPE>));
}

TTS_CASE("Check eve::is_not_finite behavior")
{
  TTS_EQUAL(eve::is_not_finite(EVE_TYPE(0)), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_finite(EVE_TYPE(2)), eve::False<EVE_TYPE>() );

  if constexpr(std::is_floating_point_v<EVE_VALUE> && eve::platform::supports_infinites)
  {
    TTS_EQUAL(eve::is_not_finite(eve::Inf<EVE_TYPE>())  , eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::is_not_finite(eve::Minf<EVE_TYPE>()) , eve::True<EVE_TYPE>());
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_not_finite(eve::Nan<EVE_TYPE>()), eve::True<EVE_TYPE>());
  }
}
