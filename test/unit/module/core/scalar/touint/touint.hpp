//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TOUINT_HPP
#define TOUINT_HPP

#include <eve/function/scalar/touint.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check touint return type") { TTS_EXPR_IS(eve::touint(Type(0)), (eve::detail::as_integer_t<Type, unsigned>)); }

TTS_CASE("Check eve::touint behavior")
{
  using r_t = eve::detail::as_integer_t<Type, unsigned>; 
  TTS_EQUAL(eve::touint(Type{1}), r_t(1));
  TTS_EQUAL(eve::touint(Type{2}), r_t(2));

  TTS_EQUAL(eve::touint(eve::Mzero<Type>()), r_t(0));
  TTS_EQUAL(eve::touint(eve::Zero<Type>()), r_t(0));
  TTS_EQUAL(eve::touint(Type(1.2357)), static_cast< r_t>(1.2357));
}

TTS_CASE("Check pedantic_(eve::touint behavior)")
{
  using r_t = eve::detail::as_integer_t<Type, unsigned>; 
  TTS_EQUAL(eve::pedantic_(eve::touint)(Type{1}), r_t(1));
  TTS_EQUAL(eve::pedantic_(eve::touint)(Type{2}), r_t(2));

  TTS_EQUAL(eve::pedantic_(eve::touint)(Type(-2)), r_t(0));
  TTS_EQUAL(eve::pedantic_(eve::touint)(eve::Mzero<Type>()), r_t(0));
  TTS_EQUAL(eve::pedantic_(eve::touint)(eve::Zero<Type>()), r_t(0));
  TTS_EQUAL(eve::pedantic_(eve::touint)(Type(1.2357)), static_cast< r_t>(1.2357));
  
 for(int i=1; i < 50 ; i*= 2)
 {
  TTS_EQUAL(eve::pedantic_(eve::touint)(Type(1.2357*i)), static_cast< r_t>(1.2357*i));   
 }
}
#endif
