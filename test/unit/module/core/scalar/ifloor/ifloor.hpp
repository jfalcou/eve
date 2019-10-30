//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFLOOR_HPP
#define IFLOOR_HPP

#include <eve/function/scalar/ifloor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/tags.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check ifloor return type")
{
  using i_t = eve::detail::as_integer_t<Type>; 
  TTS_EXPR_IS(eve::ifloor(Type()), i_t);
}
 
TTS_CASE("Check eve::ifloor behavior")
{
  using i_t = eve::detail::as_integer_t<Type>; 
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::ifloor(Type{0}), i_t(0));
    TTS_EQUAL(eve::ifloor(Type{2}), i_t(2));
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::ifloor(static_cast<Type>(-2)), i_t(-2));
    }
  }
  else if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::ifloor(eve::Inf<Type>()), eve::Valmax<i_t>());
    TTS_EQUAL(eve::ifloor(eve::Minf<Type>()), eve::Valmin<i_t>());
    TTS_EQUAL(eve::ifloor(eve::Mone<Type>()), eve::Mone<i_t>());
    TTS_EQUAL(eve::ifloor(eve::Nan<Type>()), eve::Zero<i_t>());
    TTS_EQUAL(eve::ifloor(eve::One<Type>()), eve::One<i_t>());
    TTS_EQUAL(eve::ifloor(eve::Valmax<Type>()), eve::Valmax<i_t>());
    TTS_EQUAL(eve::ifloor(Type(3) / Type(-2)), i_t(-2));
    TTS_EQUAL(eve::ifloor(Type(3) / Type(2)), i_t(1));
  }
}

#endif
