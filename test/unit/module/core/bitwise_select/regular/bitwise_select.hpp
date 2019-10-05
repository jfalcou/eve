//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SELECT_HPP
#define BITWISE_SELECT_HPP

#include <eve/function/bitwise_select.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_select return type")
{
  using i_t = eve::detail::as_integer_t<Type, unsigned>;
  TTS_EXPR_IS(eve::bitwise_select(Type(),Type(),Type()), Type);
  TTS_EXPR_IS(eve::bitwise_select(i_t(),Type(),Type()), Type);
}

TTS_CASE( "Check bitwise_select behavior")
{
  using i_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EXPR_IS(eve::bitwise_select(Type(),Type(),Type()), Type);
  TTS_EXPR_IS(eve::bitwise_select(i_t(),Type(),Type()), Type);

  std::uint64_t base = 0xF5555552F552F5F2ULL;
  i_t imask = static_cast<i_t>(base & std::uint64_t(~i_t(0)));
  Type mask = eve::bitwise_cast(imask, eve::as(Type()));

  TTS_EQUAL( eve::bitwise_select( imask
                                , eve::Allbits<Type>()
                                , eve::Zero<Type>()
                                )
                , mask
                );

  TTS_EQUAL( eve::bitwise_select( mask
                                , eve::Allbits<Type>()
                                , eve::Zero<Type>()
                                )
                , mask
                );
}

#endif
