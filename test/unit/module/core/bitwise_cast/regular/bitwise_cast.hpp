//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_CAST_HPP
#define BITWISE_CAST_HPP

#include <eve/function/scalar/bitwise_cast.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <eve/detail/meta.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_cast behavior")
{
  using ut_t = eve::detail::as_integer_t<Type, unsigned>;
  using it_t = eve::detail::as_integer_t<Type, signed>;

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_cast(Type(0), eve::as_<it_t>()), it_t(0));
    TTS_EQUAL(eve::bitwise_cast(Type(0), eve::as_<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bitwise_cast(Type(0), eve::as_<Type>()), Type(0));
    TTS_EQUAL(eve::bitwise_cast(eve::Allbits<Type>(), eve::as_<it_t>()), eve::Allbits<it_t>());
    TTS_EQUAL(eve::bitwise_cast(eve::Allbits<Type>(), eve::as_<ut_t>()), eve::Allbits<ut_t>());
    TTS_IEEE_EQUAL(eve::bitwise_cast(eve::Allbits<Type>(),eve::as_<Type>()), eve::Nan<Type>());
  }
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_cast(Type(0), eve::as_<it_t>()), it_t(0));
    TTS_EQUAL(eve::bitwise_cast(Type(0), eve::as_<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bitwise_cast(eve::Allbits<Type>(), eve::as_<it_t>()), eve::Allbits<it_t>());
    TTS_EQUAL(eve::bitwise_cast(eve::Allbits<Type>(), eve::as_<ut_t>()), eve::Allbits<ut_t>());
  }
}

#endif
