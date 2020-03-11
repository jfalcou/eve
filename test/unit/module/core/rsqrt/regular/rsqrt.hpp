//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/extract.hpp>
#include <eve/function/all.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/prev.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/sequence.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check eve::rsqrt return type")
{
  TTS_EXPR_IS(eve::rsqrt(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::rsqrt behavior")
{
  TTS_ULP_EQUAL(eve::rsqrt(EVE_TYPE(1)), (EVE_TYPE(1  )), 0.5);
  TTS_ULP_EQUAL(eve::rsqrt(EVE_TYPE(4)), (EVE_TYPE(0.5)), 0.5);

  if constexpr(std::is_floating_point_v<EVE_VALUE> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL((eve::rsqrt(eve::Nan<EVE_TYPE>())) , (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL((eve::rsqrt((EVE_TYPE(0))))             , (eve::Inf<EVE_TYPE>()));
  }
}
