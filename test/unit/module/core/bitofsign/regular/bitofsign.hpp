//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITOFSIGN_HPP
#define BITOFSIGN_HPP

#include <eve/function/bitofsign.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check bitofsign return type") { TTS_EXPR_IS(eve::bitofsign(Type()), Type); }

TTS_CASE("Check eve::bitofsign behavior")
{
  if constexpr( std::is_floating_point_v<Type>)
  {
    if constexpr( eve::platform::supports_infinites )
    {
      TTS_EQUAL(eve::bitofsign(eve::Inf<Type>()), eve::Zero<Type>());
      TTS_EQUAL(eve::bitofsign(eve::Minf<Type>()), eve::Mzero<Type>());
      TTS_EXPECT(eve::is_positive(eve::bitofsign(eve::Inf<Type>())));
      TTS_EXPECT(eve::is_negative(eve::bitofsign(eve::Minf<Type>())));
    }
    TTS_EQUAL(eve::bitofsign(eve::Zero<Type>()), eve::Zero<Type>());
    TTS_EQUAL(eve::bitofsign(eve::Mzero<Type>()), eve::Mzero<Type>());
    TTS_EXPECT(eve::is_positive(eve::bitofsign(eve::Zero<Type>())));
    TTS_EXPECT(eve::is_negative(eve::bitofsign(eve::Mzero<Type>())));
    TTS_EQUAL(eve::bitofsign(eve::One<Type>()), eve::Zero<Type>());
    TTS_EXPECT(eve::is_positive(eve::bitofsign(eve::One<Type>())));
    TTS_EQUAL(eve::bitofsign(eve::Mone<Type>()), eve::Mzero<Type>());
    TTS_EXPECT(eve::is_negative(eve::bitofsign(eve::Mone<Type>())));
  }
  else if  constexpr( std::is_unsigned_v<Type>)
  {
    TTS_EQUAL(eve::bitofsign(eve::One<Type>()), eve::Zero<Type>());
    TTS_EQUAL(eve::bitofsign(eve::Valmax<Type>()), Type(1ull << (sizeof(Type)*8-1)));
  }
  else
  {
    TTS_EQUAL(eve::bitofsign(eve::Mone<Type>()), Type(1ull << (sizeof(Type)*8-1)));
    TTS_EQUAL(eve::bitofsign(eve::One<Type>()), eve::Zero<Type>());
    TTS_EQUAL(eve::bitofsign(eve::Zero<Type>()), eve::Zero<Type>());
  }
}

#endif
