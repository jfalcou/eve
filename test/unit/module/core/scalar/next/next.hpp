//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEXT_HPP
#define NEXT_HPP

#include <eve/function/scalar/next.hpp>
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

TTS_CASE("Check next return type")
{
  TTS_EXPR_IS(eve::next(Type()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::next)(Type()), Type); 
  using i_t = eve::detail::as_integer_t<Type>; 
  TTS_EXPR_IS(eve::next(Type(), i_t()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::next)(Type(), i_t()), Type);

}

TTS_CASE("Check eve::next behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::next(Type{0}), Type(1));
    TTS_EQUAL(eve::next(Type{2}), Type(3));
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::next(static_cast<Type>(-2)), Type(-1));
    }
  }
  else if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::next(eve::Inf<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::next(eve::Minf<Type>()), eve::Valmin<Type>());
    TTS_EQUAL(eve::next(eve::Mone<Type>()), eve::Mone<Type>()+eve::Eps<Type>()/2);
    TTS_IEEE_EQUAL(eve::next(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::next(eve::One<Type>()), eve::One<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::next(eve::Valmax<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::next(eve::Zero<Type>()), eve::Bitincrement<Type>());
  }
}

TTS_CASE("Check saturated_(eve::next) behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::next)(Type{0}), Type(1));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{2}), Type(3));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>()), eve::Valmax<Type>()); 
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::saturated_(eve::next)(static_cast<Type>(-2)), Type(-1));
    }
  }
  else if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Inf<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Minf<Type>()), eve::Valmin<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Mone<Type>()), eve::Mone<Type>()+eve::Eps<Type>()/2);
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::One<Type>()), eve::One<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Zero<Type>()), eve::Bitincrement<Type>());
  }  
}

TTS_CASE(" check next with two parameters")
{
  using i_t = eve::detail::as_integer_t<Type>;

  if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::next(eve::Inf<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::next(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::next(eve::Valmax<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::next(eve::Valmax<Type>(), i_t(4)), eve::Nan<Type>());
    TTS_EQUAL(eve::next(eve::Mone<Type>(), i_t(2)), eve::Mone<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::next(eve::One<Type>(),  i_t(2)), eve::One<Type>()+eve::Eps<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::next(eve::Zero<Type>(), i_t(2)), eve::Bitincrement<Type>()+eve::Bitincrement<Type>());
  }
  else if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::next(Type{0}, i_t(2)), Type(2));
    TTS_EQUAL(eve::next(Type{2}, i_t(2)), Type(4));
  }
}

TTS_CASE(" check saturated_(next) with two parameters")
{
  using i_t = eve::detail::as_integer_t<Type>;

  if  constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Inf<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>(), i_t(4)), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::saturated_(eve::next)(eve::Nan<Type>(), i_t(2)), eve::Nan<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Mone<Type>(), i_t(2)), eve::Mone<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::One<Type>(),  i_t(2)), eve::One<Type>()+eve::Eps<Type>()+eve::Eps<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Zero<Type>(), i_t(2)), eve::Bitincrement<Type>()+eve::Bitincrement<Type>());
  }
  else if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::next)(Type{0}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{2}, i_t(2)), Type(4));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>(), i_t(2)), eve::Valmax<Type>());
  }
}

#endif
