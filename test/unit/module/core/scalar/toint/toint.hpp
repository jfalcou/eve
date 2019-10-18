//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TOINT_HPP
#define TOINT_HPP

#include <eve/function/scalar/toint.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check toint return type") { TTS_EXPR_IS(eve::toint(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE("Check eve::toint behavior")
{
  using r_t = eve::detail::as_integer_t<Type>; 
  TTS_EQUAL(eve::toint(Type{1}), r_t(1));
  TTS_EQUAL(eve::toint(Type{2}), r_t(2));

  TTS_EQUAL(eve::toint(Type(-2)), r_t(-2));
  TTS_EQUAL(eve::toint(eve::Mzero<Type>()), r_t(0));
  TTS_EQUAL(eve::toint(eve::Zero<Type>()), r_t(0));
  TTS_EQUAL(eve::toint(Type(1.2357)), static_cast< r_t>(1.2357));
}

TTS_CASE("Check pedantic_(eve::toint behavior)")
{
  using r_t = as_integer_t<Type>; 
  TTS_EQUAL(eve::pedantic_(eve::toint)(Type{1}), r_t(1));
  TTS_EQUAL(eve::pedantic_(eve::toint)(Type{2}), r_t(2));

  TTS_EQUAL(eve::pedantic_(eve::toint)(Type(-2)), r_t(-2));
  TTS_EQUAL(eve::pedantic_(eve::toint)(eve::Mzero<Type>()), r_t(0));
  TTS_EQUAL(eve::pedantic_(eve::toint)(eve::Zero<Type>()), r_t(0));
  TTS_EQUAL(eve::pedantic_(eve::toint)(Type(1.2357)), static_cast< r_t>(1.2357));
  
 for(int i=1; i < 50 ; i*= 2)
 {
  TTS_EQUAL(eve::pedantic_(eve::toint)(Type(1.2357*i)), static_cast< r_t>(1.2357*i));   
 }
}
#endif
