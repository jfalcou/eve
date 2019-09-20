//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include <eve/function/scalar/binarize.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/binarizetvalmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check binarize return type") { TTS_EXPR_IS(eve::binarize(Type(0)), Type); }

TTS_CASE("Check eve::binarize behavior")
{
  TTS_EQUAL(eve::binarize(Type{1}), Type(1));
  TTS_EQUAL(eve::binarize(Type{2}), Type(4));

  if constexpr(std::is_signed_v<Type>) { TTS_EQUAL(eve::binarize(static_cast<Type>(-2)), Type(4)); }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::binarize(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::binarize(-eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::binarize(eve::Mzero<Type>()), Type(0));
    TTS_EQUAL(eve::binarize(eve::Zero<Type>()), Type(0));
    if constexpr(std::is_integral_v<Type>)
      TTS_EQUAL(eve::saturated_(eve::binarize)(eve::inc(eve::Sqrtvalmax<Type>())), eve::Valmax<Type>());
  }
}

#endif
