//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ONEMINUS_HPP
#define ONEMINUS_HPP

#include <eve/function/scalar/oneminus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/inc.hpp> 
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check oneminus return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::oneminus)(Type(0)),  Type);
}

TTS_CASE("Check eve::saturated_(eve::oneminus) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::oneminus)(Type{1}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::oneminus[Type(1) > Type(0)])(Type(1)),  Type(0));
  TTS_EQUAL(eve::saturated_(eve::oneminus[Type(1) > Type(2)])(eve::Zero<Type>()),  Type(0));

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(Type{2}), Type(-1));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(static_cast<Type>(-2)), Type(3));
    TTS_EQUAL(eve::saturated_(eve::oneminus[Type(-1) > Type(0)])(eve::Zero<Type>()),  Type(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Valmin<Type>()), eve::Valmax<Type>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::Valmin<Type>())), eve::Valmax<Type>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::inc(eve::Valmin<Type>()))), eve::Valmax<Type>());      
  }
  if constexpr(std::is_unsigned_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(Type{2}), Type(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(Type{1}), Type(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(Type{0}), Type(1));
  }
   if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Mzero<Type>()), Type(1));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Zero<Type>()),  Type(1));
  }
}

#endif
