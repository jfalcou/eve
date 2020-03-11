//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mantissa.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check eve::mantissa return type")
{
  TTS_EXPR_IS((eve::mantissa(EVE_TYPE(0))), (EVE_TYPE));
}

TTS_CASE("Check eve::mantissa  behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL((eve::mantissa(eve::Inf<EVE_TYPE>())), (eve::Inf<EVE_TYPE>()));
    TTS_EQUAL((eve::mantissa(eve::Minf<EVE_TYPE>())), (eve::Minf<EVE_TYPE>()));
    TTS_IEEE_EQUAL((eve::mantissa(eve::Nan<EVE_TYPE>())), (eve::Nan<EVE_TYPE>()));
  }
  TTS_EQUAL((eve::mantissa(eve::Mone<EVE_TYPE>())), (eve::Mone<EVE_TYPE>()));
  TTS_EQUAL((eve::mantissa(eve::One<EVE_TYPE>())), (eve::One<EVE_TYPE>()));
  TTS_EQUAL((eve::mantissa(eve::Zero<EVE_TYPE>())), (eve::Zero<EVE_TYPE>()));
  TTS_EQUAL((eve::mantissa(EVE_TYPE(2))), eve::One<EVE_TYPE>());
  TTS_EQUAL((eve::mantissa(EVE_TYPE(1.5))), EVE_TYPE(1.5));
  TTS_EQUAL((eve::mantissa(EVE_TYPE(2.5))), EVE_TYPE(1.25)); 
}

