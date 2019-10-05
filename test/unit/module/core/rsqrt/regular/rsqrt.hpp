//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef RSQRT_HPP
#define RSQRT_HPP

#include <eve/function/rsqrt.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/half.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check rsqrt return type") { TTS_EXPR_IS(eve::rsqrt(Type(0)), Type); }

TTS_CASE("Check eve::rsqrt behavior")
{
  TTS_EQUAL(eve::rsqrt(Type{1}), Type(1));
  TTS_EQUAL(eve::rsqrt(Type{4}), eve::Half<Type>());

  if constexpr(std::is_floating_point_v<Type> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::rsqrt(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::rsqrt(-eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::rsqrt(eve::Mzero<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::rsqrt(eve::Zero<Type>()), eve::Inf<Type>());
  }
}

#endif

