//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIST_HPP
#define DIST_HPP

#include <eve/function/scalar/dist.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>    
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>


TTS_CASE("Check eve::dist behavior")
{
  TTS_EQUAL(eve::dist(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::dist(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::dist(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::dist(Type{1}, Type{1}), Type{0});
  if constexpr(std::is_integral_v<Type> && std::is_signed_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::dist[eve::saturated_](eve::Valmax<T>(), eve::Valmin<T>()), eve::Valmax<T>());
    TTS_IEEE_EQUAL(eve::dist[eve::saturated_](eve::Valmax<T>(), eve::Zero<T>()), eve::Valmax<T>());
    TTS_IEEE_EQUAL(eve::dist[eve::saturated_](eve::Valmin<T>(), eve::Zero<T>()), eve::Valmax<T>());    
  }
}

#endif
