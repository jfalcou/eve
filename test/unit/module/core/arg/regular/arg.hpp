//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ARG_HPP
#define ARG_HPP

#include <eve/function/arg.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <type_traits>


TTS_CASE("Check arg return type")
{
  TTS_EXPR_IS(eve::arg(Type(0)),  Type);
}


TTS_CASE("Check arg return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::arg)(Type(0)),  Type);
}

TTS_CASE("Check eve::pedantic_(eve::arg) behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL(eve::arg(eve::Inf<Type>()), eve::Zero<Type>());
    TTS_EQUAL(eve::arg(eve::Minf<Type>()), eve::Pi<Type>());
  }
  TTS_EQUAL(eve::arg(eve::Mone<Type>()), eve::Pi<Type>());
  TTS_EQUAL(eve::arg(eve::One<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::arg(eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::arg(eve::Mzero<Type>()), eve::Pi<Type>());
}

#endif
