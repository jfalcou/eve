//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ADD_HPP
#define ADD_HPP

#include <eve/function/scalar/add.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>


TTS_CASE("Check eve::add behavior")
{
  TTS_EQUAL(eve::add(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::add(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::add(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::add(Type{1}, Type{1}), Type{2});
}

TTS_CASE("Check saturated_(eve::add) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::add)(eve::One<Type>(), eve::One<Type>()), Type(2));
  TTS_EQUAL(eve::saturated_(eve::add)(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Minf<Type>(), eve::Minf<Type>()), eve::Minf<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::add)(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>());
  }
  else if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Mone<Type>(), eve::Mone<Type>()), Type(-2));
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Valmax<Type>(),eve::One<Type>()), eve::Valmax<Type>());
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Valmin<Type>(),eve::Mone<Type>()), eve::Valmin<Type>());
  }
  else
  {
    TTS_EQUAL(eve::saturated_(eve::add)(eve::Valmax<Type>(),eve::One<Type>()), eve::Valmax<Type>());
  } 
}


#endif
