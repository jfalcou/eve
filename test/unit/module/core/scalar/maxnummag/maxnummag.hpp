//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MAXNUMMAG_HPP
#define MAXNUMMAG_HPP

#include <eve/function/scalar/maxmag.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>


TTS_CASE("Check eve::maxmag[eve::num_] behavior")
{
  TTS_EQUAL(eve::maxmag[eve::num_](Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::maxmag[eve::num_](Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::maxmag[eve::num_](Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::maxmag[eve::num_](Type{1}, Type{2}), Type{2});
  TTS_EQUAL(eve::maxmag[eve::num_](Type{2}, Type{1}), Type{2});
  if constexpr(std::is_signed_v<Type> )
  {
    TTS_EQUAL(eve::maxmag[eve::num_](static_cast<Type>(-3), Type{2}), static_cast<Type>(-3));
    TTS_EQUAL(eve::maxmag[eve::num_](static_cast<Type>(-1), Type{2}), static_cast<Type>(2));
    TTS_EQUAL(eve::maxmag[eve::num_](static_cast<Type>(-1), Type{1}), Type{1}); 
  }
  if constexpr(std::is_floating_point_v<Type> )
  {
    Type n =  eve::Nan<Type>();
    Type o =  eve::One<Type>();
    TTS_IEEE_EQUAL(eve::maxmag[eve::num_](n, o), o);
    TTS_IEEE_EQUAL(eve::maxmag[eve::num_](o, n), o);
  }
}

#endif
