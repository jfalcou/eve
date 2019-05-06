//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INC_HPP
#define INC_HPP

#include <eve/function/scalar/inc.hpp>
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

TTS_CASE("Check inc return type")
{
  TTS_EXPR_IS(eve::inc(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::inc behavior")
{
  TTS_EQUAL(eve::inc(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::inc(Type{2}), eve::False<Type>());

  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::inc(static_cast<Type>(-2)), eve::True<Type>());
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::inc(eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::inc(-eve::Nan<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::inc(eve::Mzero<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::inc(eve::Zero<Type>()), eve::False<Type>());
  }
}

#endif
