//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_NOTOR_HPP
#define BITWISE_NOTOR_HPP

#include <eve/function/bitwise_notor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_notor return type")
{
  TTS_EXPR_IS(eve::bitwise_notor(Type(), Type()), Type);
  TTS_EXPR_IS(eve::bitwise_notor(Type(), eve::detail::as_integer_t<Type>()), Type);
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>;
  TTS_EXPR_IS(eve::bitwise_notor(Type(),ui_t()) , Type);
  TTS_EXPR_IS(eve::bitwise_notor(Type(),si_t()) , Type);
  TTS_EXPR_IS(eve::bitwise_notor(ui_t(), Type()), ui_t);
  TTS_EXPR_IS(eve::bitwise_notor(si_t(), Type()), si_t);
}

TTS_CASE( "Check bitwise_notor behavior")
{
  TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::One<Type>()), eve::One<Type>());
  TTS_IEEE_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_IEEE_EQUAL(eve::bitwise_notor(eve::Zero<Type>(), eve::Allbits<Type>()), eve::Allbits<Type>());
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_notor(Type(2), Type(3)), eve::Allbits<Type>());
    TTS_EQUAL(eve::bitwise_notor(Type(1), Type(1)), eve::Allbits<Type>());
    using ui_t = eve::detail::as_integer_t<Type, unsigned>;
    using si_t = eve::detail::as_integer_t<Type, signed>;
    TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::One<ui_t>()), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_notor(eve::Allbits<Type>(), eve::One<si_t>()), eve::One<Type>());
    TTS_EQUAL(eve::bitwise_notor(eve::Allbits<ui_t>(), eve::One<Type>()), eve::One<ui_t>());
    TTS_EQUAL(eve::bitwise_notor(eve::Allbits<si_t>(), eve::One<Type>()), eve::One<si_t>());
  }
}

#endif
