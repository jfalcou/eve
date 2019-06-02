//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INC_HPP
#define INC_HPP

#include <eve/function/scalar/inc.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

#if defined(EVE_COMP_IS_MSVC)
#pragma warning( push )
#pragma warning( disable : 4146 ) // unary - on unsigned (?)
#endif

TTS_CASE("Check inc return type")
{
  TTS_EXPR_IS(eve::inc(Type(0)),  Type);
}

TTS_CASE("Check eve::inc behavior")
{
  TTS_EQUAL(eve::inc(Type{0}), Type(1));
  TTS_EQUAL(eve::inc(Type{2}), Type(3));
  TTS_EQUAL(eve::inc[Type(1) > Type(0)](eve::Zero<Type>()),  Type(1));
  TTS_EQUAL(eve::inc[Type(1) > Type(2)](eve::Zero<Type>()),  Type(0));

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::inc(static_cast<Type>(-2)), Type(-1));
    TTS_EQUAL(eve::inc[Type(-1) > Type(0)](eve::Zero<Type>()),  Type(0));
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::inc(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::inc(-eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::inc(eve::Mzero<Type>()), Type(1));
    TTS_EQUAL(eve::inc(eve::Zero<Type>()),  Type(1));
  }
}

#if defined(EVE_COMP_IS_MSVC)
#pragma warning( pop )
#endif

#endif
