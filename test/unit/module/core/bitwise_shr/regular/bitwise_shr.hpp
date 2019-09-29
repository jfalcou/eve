//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SHR_HPP
#define BITWISE_SHR_HPP

#include <eve/function/scalar/bitwise_shr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_shr return type")
{
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>; 
  TTS_EXPR_IS(eve::bitwise_shr(Type(), int()),  Type);
  TTS_EXPR_IS(eve::bitwise_shr(Type(), ui_t()), Type);
  TTS_EXPR_IS(eve::bitwise_shr(Type(), si_t()), Type);
}

TTS_CASE( "Check bitwise_shr behavior")
{
  TTS_EQUAL(eve::bitwise_shr(Type(2),1), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_shr(eve::One<Type>(),1), eve::Zero<Type>());
  TTS_EQUAL(eve::bitwise_shr(Type(4), 1),  Type(2)); 
  TTS_EQUAL(eve::bitwise_shr(eve::Zero<Type>(),1), eve::Zero<Type>());
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_shr(eve::Mone<Type>(),(sizeof(Type)*8-1)), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_shr(eve::Mone<Type>(),(sizeof(Type)*8-2)), Type(3));
  }
  else
  {
    TTS_EQUAL(eve::bitwise_shr(eve::Valmax<Type>(),(sizeof(Type)*8-1)), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_shr(eve::Valmax<Type>(),(sizeof(Type)*8-2)), Type(3));
  }
}

#endif
