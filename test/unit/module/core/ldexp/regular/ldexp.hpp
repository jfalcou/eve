//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ldexp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>    
#include <type_traits>

TTS_CASE("Check ldexp return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Value, signed>;
  using su_t = eve::detail::as_integer_t<Value, unsigned>;

  TTS_EXPR_IS((eve::ldexp(Type(), i_t())), (Type));
  TTS_EXPR_IS((eve::ldexp(Type(), u_t())), (Type));  
  TTS_EXPR_IS((eve::ldexp(Type(), si_t())), (Type));
  TTS_EXPR_IS((eve::ldexp(Type(), su_t())), (Type));  
}


TTS_CASE("Check eve::ldexp behavior")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using si_t = eve::detail::as_integer_t<Value, signed>;

    TTS_EQUAL(eve::ldexp(Type{0}, i_t(2)), Type(0));
    TTS_EQUAL(eve::ldexp(Type{1}, i_t(2)), Type(4));
    TTS_EQUAL(eve::ldexp(Type{0}, si_t(2)),Type(0));
    TTS_EQUAL(eve::ldexp(Type{1}, si_t(2)),Type(4));

    TTS_EQUAL(eve::ldexp(Type(-1), i_t(2)), Type(-4));
    TTS_EQUAL(eve::ldexp(Type(-2), i_t(2)), Type(-8));
    TTS_EQUAL(eve::ldexp(Type(-1), si_t(2)),Type(-4));
    TTS_EQUAL(eve::ldexp(Type(-2), si_t(2)),Type(-8));

}
