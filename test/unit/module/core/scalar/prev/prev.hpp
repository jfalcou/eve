//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef PREV_HPP
#define PREV_HPP

#include <eve/function/scalar/prev.hpp>
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
#include <eve/constant/bitincrement.hpp>
#include <eve/tags.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check prev return type")
{
  TTS_EXPR_IS(eve::prev(Type()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::prev)(Type()), Type); 
  using i_t = eve::detail::as_integer_t<Type>; 
  TTS_EXPR_IS(eve::prev(Type(), i_t()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::prev)(Type(), i_t()), Type);

}

TTS_CASE("Check eve::prev behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::prev(Type{1}), Type(0));
    TTS_EQUAL(eve::prev(Type{2}), Type(1));
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::prev(static_cast<Type>(-2)), Type(-3));
    }
  }
  else if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::prev(eve::Inf<Type>()), eve::Valmax<Type>());
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::prev(eve::Mone<Type>()), eve::Mone<Type>()-eve::Eps<Type>());
    TTS_IEEE_EQUAL(eve::prev(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::prev(eve::One<Type>()), eve::One<Type>()-eve::Eps<Type>()/2);
    TTS_EQUAL(eve::prev(eve::Zero<Type>()), -eve::Bitincrement<Type>());
  }
}

TTS_CASE("Check saturated_(eve::prev) behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{1}), Type(0));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{2}), Type(1));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>()), eve::Valmin<Type>()); 
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::saturated_(eve::prev)(static_cast<Type>(-2)), Type(-3));
    }
  }
  else if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Inf<Type>()), eve::Valmax<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Minf<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Mone<Type>()), eve::Mone<Type>()-eve::Eps<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::One<Type>()), eve::One<Type>()-eve::Eps<Type>()/2);
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>()), eve::Minf<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Zero<Type>()), -eve::Bitincrement<Type>());
  }  
}

TTS_CASE(" check prev with two parameters")
{
  using i_t = eve::detail::as_integer_t<Type>;

  if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::prev(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::prev(eve::Valmin<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::prev(eve::Valmin<Type>(), i_t(4)), eve::Nan<Type>());
    TTS_EQUAL(eve::prev(eve::Mone<Type>(), i_t(2)), eve::Mone<Type>()-eve::Eps<Type>()*2);
    TTS_EQUAL(eve::prev(eve::One<Type>(),  i_t(2)), eve::One<Type>()-eve::Eps<Type>());
    TTS_EQUAL(eve::prev(eve::Zero<Type>(), i_t(2)), -eve::Bitincrement<Type>()-eve::Bitincrement<Type>());
  }
  else if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::prev(Type{4}, i_t(2)), Type(2));
    TTS_EQUAL(eve::prev(Type{6}, i_t(2)), Type(4));
  }
}

TTS_CASE(" check saturated_(prev) with two parameters")
{
  using i_t = eve::detail::as_integer_t<Type>;
  
  if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Minf<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>(), i_t(4)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::prev)(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Mone<Type>(), i_t(2)), eve::Mone<Type>()-eve::Eps<Type>()*2);
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::One<Type>(),  i_t(2)), eve::One<Type>()-eve::Eps<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Zero<Type>(), i_t(2)), -eve::Bitincrement<Type>()-eve::Bitincrement<Type>());
  }
  else if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{4}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{6}, i_t(2)), Type(4));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>(), i_t(2)), eve::Valmin<Type>());
  }
}

#endif
