//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

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


// TTS_CASE("Check bitwise_cast return type") in individual types due to compilation problems with clang
// "check not constant"
// and with g++ with floating points
//      using ft_t = eve::detail::as_floating_point_t<Type>;
// as seen above

TTS_CASE("Check eve::bitwise_cast behavior")
{
  using ut_t = eve::detail::as_integer_t<Type, unsigned>;
  using it_t = eve::detail::as_integer_t<Type, signed>;
  
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_cast<it_t>(Type(0)), it_t(0));
    TTS_EQUAL(eve::bitwise_cast<ut_t>(Type(0)), ut_t(0));
    TTS_EQUAL(eve::bitwise_cast<Type>(Type(0)), Type(0));
    TTS_EQUAL(eve::bitwise_cast<it_t>(eve::Allbits<Type>()), eve::Allbits<it_t>());
    TTS_EQUAL(eve::bitwise_cast<ut_t>(eve::Allbits<Type>()), eve::Allbits<ut_t>());
    TTS_IEEE_EQUAL(eve::bitwise_cast<Type>(eve::Allbits<Type>()), eve::Nan<Type>());
  }
  if  constexpr(std::is_integral_v<Type>)
  {
    if constexpr(sizeof(Type) >= 4)
    {
//      using ft_t = eve::detail::as_floating_point_t<Type>;
      TTS_EQUAL(eve::bitwise_cast<it_t>(Type(0)), it_t(0));
      TTS_EQUAL(eve::bitwise_cast<ut_t>(Type(0)), ut_t(0));
//      TTS_EQUAL(eve::bitwise_cast<ft_t>(Type(0)), ft_t(0));      
      TTS_EQUAL(eve::bitwise_cast<it_t>(eve::Allbits<Type>()), eve::Allbits<it_t>());
      TTS_EQUAL(eve::bitwise_cast<ut_t>(eve::Allbits<Type>()), eve::Allbits<ut_t>());
      //     TTS_IEEE_EQUAL(eve::bitwise_cast<ft_t>(eve::Allbits<Type>()), ft_t(eve::Allbits<Type>()));      
    }
    else
    {
      TTS_EQUAL(eve::bitwise_cast<it_t>(Type(0)), it_t(0));
      TTS_EQUAL(eve::bitwise_cast<ut_t>(Type(0)), ut_t(0));      
      TTS_EQUAL(eve::bitwise_cast<it_t>(eve::Allbits<Type>()), eve::Allbits<it_t>());
      TTS_EQUAL(eve::bitwise_cast<ut_t>(eve::Allbits<Type>()), eve::Allbits<ut_t>());     
    }
  }
}

#endif
