//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_POSITIVE_HPP
#define IS_POSITIVE_HPP

#include <eve/function/scalar/is_positive.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(push)
#  pragma warning(disable : 4146) // unary - on unsigned (?)
#endif

TTS_CASE("Check is_positive return type")
{
  TTS_EXPR_IS(eve::is_positive(Type(0)), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_positive behavior")
{
  TTS_EQUAL(eve::is_positive(Type{0}), eve::True<Type>());
  TTS_EQUAL(eve::is_positive(Type{2}), eve::True<Type>());

  if constexpr(std::is_signed_v<Type>)
  { TTS_EQUAL(eve::is_positive(static_cast<Type>(-2)), eve::False<Type>()); }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_positive(-eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_positive(eve::Nan<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_positive(eve::Mzero<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_positive(eve::Zero<Type>()), eve::True<Type>());
  }
}

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(pop)
#endif

#endif
