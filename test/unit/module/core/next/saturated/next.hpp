//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/next.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE("Check saturated next return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Value, signed>;
  using su_t = eve::detail::as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::saturated_(eve::next)(Type()), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::next)(Type(), i_t())), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::next)(Type(), u_t())), (Type));  
  TTS_EXPR_IS((eve::saturated_(eve::next)(Type(), si_t())), (Type));
  TTS_EXPR_IS((eve::saturated_(eve::next)(Type(), su_t())), (Type));  
}

TTS_CASE("Check eve::saturated_(eve::next) one parameter behavior")
{
  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::next)(Type{0}), Type(1));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{1}), Type(2));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>()), eve::Valmax<Type>()); 
    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-1)), Type(0));
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-2)), Type(-1));
    }
  }
  else
  {
    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Inf<Type>())), (eve::Nan<Type>()));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>())  , eve::Inf<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Minf<Type>())    , eve::Valmin<Type>());
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Mone<Type>())    , eve::Mone<Type>()+eve::Eps<Type>()/2);
    TTS_EQUAL(eve::saturated_(eve::next)(eve::One<Type>())     , eve::One<Type>()+eve::Eps<Type>());
  }
}

TTS_CASE("Check eve::saturated_(eve::next) two parameters behavior")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using si_t = eve::detail::as_integer_t<Value, signed>;

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::next)(Type{0}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{1}, i_t(2)), Type(3));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{0}, si_t(2)),Type(2));
    TTS_EQUAL(eve::saturated_(eve::next)(Type{1}, si_t(2)),Type(3));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Type>(), i_t(2)), eve::Valmax<Type>());
    
    TTS_EQUAL(eve::saturated_(eve::next)(Value{0}, i_t(2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::next)(Value{1}, i_t(2)), Type(3));
    TTS_EQUAL(eve::saturated_(eve::next)(eve::Valmax<Value>(), i_t(2)), eve::Valmax<Type>());

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-1), i_t(2)), Type(1));
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-2), i_t(2)), Type(0));
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-1), si_t(2)),Type(1));
      TTS_EQUAL(eve::saturated_(eve::next)(Type(-2), si_t(2)),Type(0));

      TTS_EQUAL(eve::saturated_(eve::next)(Value(-1), i_t(2)), Type(1));
      TTS_EQUAL(eve::saturated_(eve::next)(Value(-2), i_t(2)), Type(0));
    }
  }
  else
  {
    TTS_EQUAL(0, 0); 
    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Inf<Type>(), i_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Valmax<Type>(), i_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::Mone<Type>(), i_t(2)))       , (eve::Mone<Type>()+eve::Eps<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::One<Type>(), i_t(2)))        , (eve::One<Type>()+eve::Eps<Type>()*2));

    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Inf<Type>(), si_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Valmax<Type>(), si_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::Mone<Type>(), si_t(2)))       , (eve::Mone<Type>()+eve::Eps<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::One<Type>(), si_t(2)))        , (eve::One<Type>()+eve::Eps<Type>()*2));

    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Inf<Value>(), i_t(2)))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::saturated_(eve::next)(eve::Valmax<Value>(), i_t(2))), (eve::Nan<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::Mone<Value>(), i_t(2)))       , (eve::Mone<Type>()+eve::Eps<Type>()));
    TTS_EQUAL((eve::saturated_(eve::next)(eve::One<Value>(), i_t(2)))        , (eve::One<Type>()+eve::Eps<Type>()*2));
  }
}
