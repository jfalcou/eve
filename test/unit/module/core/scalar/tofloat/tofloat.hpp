//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TOFLOAT_HPP
#define TOFLOAT_HPP

#include <eve/function/scalar/tofloat.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check tofloat return type") { TTS_EXPR_IS(eve::tofloat(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE("Check eve::tofloat behavior")
{
  using r_t = eve::detail::as_integer_t<Type>; 
  TTS_EQUAL(eve::tofloat(Type{1}), r_t(1));
  TTS_EQUAL(eve::tofloat(Type{2}), r_t(2));

  TTS_EQUAL(eve::tofloat(Type(-2)), r_t(-2));
  TTS_EQUAL(eve::tofloat(eve::Mzero<Type>()), r_t(0));
  TTS_EQUAL(eve::tofloat(eve::Zero<Type>()), r_t(0));
  TTS_EQUAL(eve::tofloat(Type(1.2357)), static_cast< r_t>(1.2357));
}

#endif
