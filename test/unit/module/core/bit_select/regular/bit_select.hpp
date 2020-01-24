//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_select.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::bit_select return type")
{
  using i_t = eve::detail::as_integer_t<Type, unsigned>;
  TTS_EXPR_IS(eve::bit_select(Type(),Type() ,Type() ), (Type));
  TTS_EXPR_IS(eve::bit_select(Type(),Type() ,Value()), (Type));
  TTS_EXPR_IS(eve::bit_select(Type(),Value(),Type() ), (Type));
  TTS_EXPR_IS(eve::bit_select( i_t(),Type() ,Type() ), (Type));
  TTS_EXPR_IS(eve::bit_select( i_t(),Type() ,Value()), (Type));
  TTS_EXPR_IS(eve::bit_select( i_t(),Value(),Type() ), (Type));
}

TTS_CASE( "Check eve::bit_select behavior")
{
  using i_t  = eve::detail::as_integer_t<Type, unsigned>;
  using vi_t = eve::detail::as_integer_t<Value, unsigned>;

  std::uint64_t base  = 0xF5555552F552F5F2ULL;
  i_t           imask = static_cast<i_t>(base & std::uint64_t(~vi_t(0)));
  Type          mask  = eve::bit_cast(imask, eve::as(Type()));

  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<Type>() , eve::Zero<Type>() ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<Value>(), eve::Zero<Type>() ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<Type>() , eve::Zero<Value>()), mask );

  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<Type>()  , eve::Zero<Type>() ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<Value>() , eve::Zero<Type>() ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<Type>()  , eve::Zero<Value>()), mask);
}
