//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEXTAFTER_HPP
#define NEXTAFTER_HPP

#include <eve/function/scalar/nextafter.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>   
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/bitincrement.hpp>
#include <type_traits>

TTS_CASE("Check eve::nextafter return type") { TTS_EXPR_IS(eve::nextafter(Type(), Type()), Type); }

TTS_CASE("Check eve::nextafter behavior")
{
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::nextafter(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::nextafter(eve::Minf<Type>(), eve::One<Type>()), eve::Valmin<Type>());
    TTS_IEEE_EQUAL(eve::nextafter(eve::Nan<Type>(), eve::One<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::nextafter(eve::One<Type>(), eve::Inf<Type>()), eve::One<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::nextafter(eve::Valmax<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::nextafter(eve::Mone<Type>(), eve::One<Type>()), eve::Mone<Type>()+eve::Eps<Type>()/2);
    TTS_EQUAL(eve::nextafter(eve::Zero<Type>(), eve::One<Type>()), eve::Bitincrement<Type>());
    //non standard behaviour
    TTS_IEEE_EQUAL(eve::nextafter(eve::One<Type>(), eve::Nan<Type>()), eve::One<Type>());   
   }
  TTS_EQUAL(eve::nextafter(Type(1), Type(3)), eve::next(Type(1)));
  TTS_EQUAL(eve::nextafter(Type(5), Type(3)), eve::prev(Type(5)));
  TTS_EQUAL( eve::nextafter(Type(5), Type(5)), Type(5)); 
}

TTS_CASE("Check eve::pedantic_(eve::nextafter) behavior")
{
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::Minf<Type>(), eve::One<Type>()), eve::Valmin<Type>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::nextafter)(eve::Nan<Type>(), eve::One<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::One<Type>(), eve::Inf<Type>()), eve::One<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::Valmax<Type>(), eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::Mone<Type>(), eve::One<Type>()), eve::Mone<Type>()+eve::Eps<Type>()/2);
    TTS_EQUAL(eve::pedantic_(eve::nextafter)(eve::Zero<Type>(), eve::One<Type>()), eve::Bitincrement<Type>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::nextafter)(eve::One<Type>(), eve::Nan<Type>()), eve::Nan<Type>()); 
  }
  TTS_EQUAL(eve::pedantic_(eve::nextafter)(Type(1), Type(3)), eve::next(Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::nextafter)(Type(5), Type(3)), eve::prev(Type(5)));
  TTS_EQUAL( eve::pedantic_(eve::nextafter)(Type(5), Type(5)), Type(5)); 
}

#endif
