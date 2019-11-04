//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE("Check saturated prev return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Value, signed>;
  using su_t = eve::detail::as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::saturated_(eve::prev)(Type()), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::prev)(Type(), i_t())), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::prev)(Type(), u_t())), (Type));  
  TTS_EXPR_IS((eve::saturated_(eve::prev)(Type(), si_t())), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::prev)(Type(), su_t())), (Type));  
}

TTS_CASE("Check eve::saturated_(eve::prev) one parameter behavior")
{
  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{2}), Type(1));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{3}), Type(2));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>()), eve::Valmin<Type>()); 
    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-2)), Type(-3));
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-1)), Type(-2));
    }
  }
  else
  {
    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Minf<Type>())), (eve::Nan<Type>()));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>())  , eve::Minf<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Inf<Type>())    , eve::Valmax<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Mone<Type>())    , eve::Mone<Type>()-eve::Eps<Type>());
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::One<Type>())     , eve::One<Type>()-eve::Eps<Type>()/2);
  }
}

TTS_CASE("Check eve::saturated_(eve::prev) two parameters behavior")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using si_t = eve::detail::as_integer_t<Value, signed>;

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{4}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{5}, i_t(2)), Type(3));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{4}, si_t(2)),Type(2));
    TTS_EQUAL(eve::saturated_(eve::prev)(Type{5}, si_t(2)),Type(3));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Type>(), i_t(2)), eve::Valmin<Type>());
    
    TTS_EQUAL(eve::saturated_(eve::prev)(Value{4}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::prev)(Value{5}, i_t(2)), Type(3));
    TTS_EQUAL(eve::saturated_(eve::prev)(eve::Valmin<Value>(), i_t(2)), eve::Valmin<Type>());

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-1), i_t(2)), Type(-3));
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-2), i_t(2)), Type(-4));
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-1), si_t(2)),Type(-3));
      TTS_EQUAL(eve::saturated_(eve::prev)(Type(-2), si_t(2)),Type(-4));

      TTS_EQUAL(eve::saturated_(eve::prev)(Value(-1), i_t(2)), Type(-3));
      TTS_EQUAL(eve::saturated_(eve::prev)(Value(-2), i_t(2)), Type(-4));
    }
  }
  else
  {
    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Minf<Type>(), i_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Valmin<Type>(), i_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::Mone<Type>(), i_t(2)))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::One<Type>(), i_t(2)))        , (eve::One<Type>()-eve::Eps<Type>()));

    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Minf<Type>(), si_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Valmin<Type>(), si_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::Mone<Type>(), si_t(2)))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::One<Type>(), si_t(2)))        , (eve::One<Type>()-eve::Eps<Type>()));

    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Minf<Value>(), i_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::prev)(eve::Valmin<Value>(), i_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::Mone<Value>(), i_t(2)))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL((eve::saturated_(eve::prev)(eve::One<Value>(), i_t(2)))        , (eve::One<Type>()-eve::Eps<Type>()));
  }
}
