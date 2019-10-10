//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FREXP_HPP
#define FREXP_HPP

#include <eve/function/frexp.hpp>
#include <eve/function/ldexp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/platform.hpp>
#include <eve/detail/meta.hpp>
#include <tuple>
#include <cstdlib>

TTS_CASE("Check raw_(eve::frexp) behavior")
{

  TTS_EXPR_IS ( (eve::raw_(eve::frexp)(Type(0)))
              , (std::tuple<Type,Type>)
              );
  
  auto [m, e] = eve::raw_(eve::frexp)(Type(1)); 
  TTS_EQUAL(m  , Type(0.5));
  TTS_EQUAL(e , Type(1));
  std::tie(m, e) = eve::raw_(eve::frexp)(eve::Valmax<Type>());
  TTS_ULP_EQUAL (m , Type(1)-eve::Eps<Type>()/2, 0.5);
  TTS_EQUAL(e , Type(eve::Limitexponent<Type>()));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(m, e),eve::Valmax<Type>());
}

TTS_CASE("Check eve::frexp behavior")
{
  TTS_EXPR_IS ( (eve::frexp(Type(0)))
              , (std::tuple<Type,Type>)
              );
  
  auto [m, e] = eve::frexp(Type(1));
  TTS_EQUAL(m  , Type(0.5));
  TTS_EQUAL(e , Type(1));
  std::tie(m, e) = eve::frexp(eve::Valmax<Type>());
  TTS_ULP_EQUAL (m , Type(1)-eve::Eps<Type>()/2, 0.5);
  TTS_EQUAL(e , Type(eve::Limitexponent<Type>()));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(m, e),eve::Valmax<Type>());
  std::tie(m, e) = eve::frexp(eve::Zero<Type>());
  TTS_EQUAL (m , eve::Zero<Type>());
  TTS_EQUAL(e ,  eve::Zero<Type>()); 
  TTS_EQUAL(eve::ldexp(m, e),eve::Zero<Type>());
}

TTS_CASE("Check pedantic_(eve::frexp) behavior")
{
  TTS_EXPR_IS ( (eve::pedantic_(eve::frexp)(Type(0)))
              , (std::tuple<Type,Type>)
              );
  
  auto [m, e] = eve::pedantic_(eve::frexp)(Type(1));
  TTS_EQUAL(m  , Type(0.5));
  TTS_EQUAL(e , Type(1));
  std::tie(m, e) = eve::pedantic_(eve::frexp)(eve::Valmax<Type>());
  TTS_ULP_EQUAL (m , Type(1)-eve::Eps<Type>()/2, 0.5);
  TTS_EQUAL(e , Type(eve::Limitexponent<Type>()));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(m, e),eve::Valmax<Type>());
  std::tie(m, e) = eve::frexp(eve::Zero<Type>());
  TTS_EQUAL (m , eve::Zero<Type>());
  TTS_EQUAL(e ,  eve::Zero<Type>());
  TTS_EQUAL(eve::ldexp(m, e),eve::Zero<Type>());
  std::tie(m, e) = eve::pedantic_(eve::frexp)(eve::Smallestposval<Type>()/2);
  TTS_EQUAL (m , eve::Half<Type>());
  TTS_EQUAL(e ,  Type(eve::Minexponent<Type>()));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(m, e),eve::Smallestposval<Type>()/2);
}



#endif
