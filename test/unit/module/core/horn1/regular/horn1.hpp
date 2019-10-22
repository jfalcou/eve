//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core/detail/generic/horn1.hpp>
#include <tts/tests/relation.hpp>
#include <type_traits>

#ifndef HORN1_INCLUDED
#define HORN1_INCLUDED
template<typename T> constexpr auto coeff0()
{
  if constexpr( std::is_same_v<T, float> )  return 0x00000000U;
  else                                      return 0x00000000ULL;
}

template<typename T> constexpr auto coeff1()
{
  if constexpr( std::is_same_v<T, float> )  return 0x3f800000U;
  else                                      return 0x3FF0000000000000ULL;
}

template<typename T> constexpr auto coeff2()
{
  if constexpr( std::is_same_v<T, float> )  return 0x40000000U;
  else                                      return 0x4000000000000000ULL;
}
#endif

TTS_CASE("Check eve::horn1 behavior")
{
  using eve::detail::horn1;

  TTS_EQUAL((horn1<Type, coeff0<Value>()>(Type(0)))                                  , (Type(0)));
  TTS_EQUAL((horn1<Type, coeff1<Value>(), coeff0<Value>(), coeff1<Value>()>(Type(1))), (Type(3)));
  TTS_EQUAL((horn1<Type, coeff2<Value>(), coeff1<Value>(), coeff1<Value>()>(Type(2))), (Type(16)));
}
