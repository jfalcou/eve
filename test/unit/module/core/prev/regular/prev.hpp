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
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <type_traits>

TTS_CASE("Check prev return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Value, signed>;
  using su_t = eve::detail::as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::prev(Type()), (Type));
  TTS_EXPR_IS((eve::prev(Type(), i_t())), (Type));
  TTS_EXPR_IS((eve::prev(Type(), u_t())), (Type));  
  TTS_EXPR_IS((eve::prev(Type(), si_t())), (Type));
  TTS_EXPR_IS((eve::prev(Type(), su_t())), (Type));  
}

TTS_CASE("Check eve::prev one parameter behavior")
{
  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::prev(Type{2}), Type(1));
    TTS_EQUAL(eve::prev(Type{3}), Type(2));
    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::prev(Type(-1)), Type(-2));
      TTS_EQUAL(eve::prev(Type(-2)), Type(-3));
    }
  }
  else
  {
    TTS_EQUAL(eve::prev(eve::Inf<Type>()), (eve::Valmax<Type>()));
    TTS_EQUAL(eve::prev(eve::Valmin<Type>())  , (eve::Minf<Type>()));
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Type>())    , (eve::Nan<Type>()));
    TTS_EQUAL(eve::prev(eve::Mone<Type>())    , (eve::Mone<Type>()-eve::Eps<Type>()));
    TTS_EQUAL(eve::prev(eve::One<Type>())     , (eve::One<Type>()-eve::Eps<Type>()/2));
    TTS_EQUAL(eve::prev(eve::Zero<Type>())    , (eve::Mzero<Type>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::prev(eve::Zero<Type>())))); 
    TTS_EQUAL(eve::prev(eve::Mzero<Type>())    , (-eve::Mindenormal<Type>()));
    TTS_EXPECT(eve::all(eve::is_positive(eve::prev(eve::Mindenormal<Type>())))); 
    TTS_EQUAL(eve::prev(eve::Mindenormal<Type>())    , (eve::Zero<Type>()));
  }
}

TTS_CASE("Check eve::prev two parameters behavior")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using si_t = eve::detail::as_integer_t<Value, signed>;

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::prev(Type{3}, i_t(2)), Type(1));
    TTS_EQUAL(eve::prev(Type{5}, i_t(2)), Type(3));
    TTS_EQUAL(eve::prev(Type{4}, si_t(2)),Type(2));
    TTS_EQUAL(eve::prev(Type{5}, si_t(2)),Type(3));
    
    TTS_EQUAL(eve::prev(Value{4}, i_t(2)), Type(2));
    TTS_EQUAL(eve::prev(Value{5}, i_t(2)), Type(3));

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::prev(Type(-1), i_t(2)), Type(-3));
      TTS_EQUAL(eve::prev(Type(-2), i_t(2)), Type(-4));
      TTS_EQUAL(eve::prev(Type(-1), si_t(2)),Type(-3));
      TTS_EQUAL(eve::prev(Type(-2), si_t(2)),Type(-4));

      TTS_EQUAL(eve::prev(Value(-1), i_t(2)), Type(-3));
      TTS_EQUAL(eve::prev(Value(-2), i_t(2)), Type(-4));
    }
  }
  else
  {
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Type>(), i_t(2))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL(eve::prev(eve::Valmin<Type>(), i_t(2)), (eve::Nan<Type>()));
    TTS_EQUAL(eve::prev(eve::Mone<Type>(), i_t(2))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL(eve::prev(eve::One<Type>(), i_t(2))        , (eve::One<Type>()-eve::Eps<Type>()));
    
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Type>(), si_t(2))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL(eve::prev(eve::Valmin<Type>(), si_t(2)), (eve::Nan<Type>()));
    TTS_EQUAL(eve::prev(eve::Mone<Type>(), si_t(2))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL(eve::prev(eve::One<Type>(), si_t(2))        , (eve::One<Type>()-eve::Eps<Type>()));
    
    TTS_IEEE_EQUAL(eve::prev(eve::Minf<Value>(), i_t(2))   , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL(eve::prev(eve::Valmin<Value>(), i_t(2)), (eve::Nan<Type>()));
    TTS_EQUAL(eve::prev(eve::Mone<Value>(), i_t(2))       , (eve::Mone<Type>()-eve::Eps<Type>()*2));
    TTS_EQUAL(eve::prev(eve::One<Value>(), i_t(2))        , (eve::One<Type>()-eve::Eps<Type>()));

    TTS_EQUAL(eve::prev(eve::Zero<Type>(), 1)             , (eve::Mzero<Type>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::prev(eve::Zero<Type>(), 1) ))); 
    TTS_EQUAL(eve::prev(eve::Mzero<Type>(), 1)            , (-eve::Mindenormal<Type>()));
    TTS_EQUAL(eve::prev(eve::Zero<Type>(), 2)             , (-eve::Mindenormal<Type>()));
    TTS_EQUAL(eve::prev(eve::Mindenormal<Type>(), 3)      , (-eve::Mindenormal<Type>()));
    TTS_EQUAL(eve::prev(eve::Mindenormal<Type>(), 2)      , (eve::Zero<Type>()));
    TTS_EQUAL(eve::prev(eve::Mindenormal<Type>(), 1)      , (eve::Mzero<Type>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::prev(eve::Mindenormal<Type>(), 2) ))); 
    TTS_EXPECT(eve::all(eve::is_positive(eve::prev(eve::Mindenormal<Type>(), 1) ))); 
  }
}
