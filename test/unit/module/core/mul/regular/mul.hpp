//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MUL_HPP
#define MUL_HPP

#include <eve/function/scalar/mul.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::mul behavior")
{
  TTS_EQUAL(eve::mul(eve::One<Type>(), eve::One<Type>()), Type(1));
  TTS_EQUAL(eve::mul(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  if constexpr(std::is_integral_v<Type>)
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::mul(eve::Mone<Type>(), eve::Mone<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::mul(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::mul(eve::Valmax<Type>(),eve::Mone<Type>()), eve::Valmin<Type>()+eve::One<Type>());
      TTS_EQUAL(eve::mul(eve::Valmax<Type>(),eve::One<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::mul(eve::Valmin<Type>(),eve::Mone<Type>()), eve::Valmin<Type>());
      TTS_EQUAL(eve::mul(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
    }
    else
    {
      TTS_EQUAL(eve::mul(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::mul(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
    }
  }
  else if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::mul(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::mul(eve::Minf<Type>(), eve::Minf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::mul(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>());
  }
}

#endif
