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
  using i_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  TTS_EXPR_IS(eve::bit_select(EVE_TYPE(),EVE_TYPE() ,EVE_TYPE() ), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_select(EVE_TYPE(),EVE_TYPE() ,EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_select(EVE_TYPE(),EVE_VALUE(),EVE_TYPE() ), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_select( i_t(),EVE_TYPE() ,EVE_TYPE() ), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_select( i_t(),EVE_TYPE() ,EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_select( i_t(),EVE_VALUE(),EVE_TYPE() ), (EVE_TYPE));
}

TTS_CASE( "Check eve::bit_select behavior")
{
  using i_t  = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;

  std::uint64_t base  = 0xF5555552F552F5F2ULL;
  i_t           imask = static_cast<i_t>(base & std::uint64_t(~vi_t(0)));
  EVE_TYPE          mask  = eve::bit_cast(imask, eve::as(EVE_TYPE()));

  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<EVE_TYPE>() , eve::Zero<EVE_TYPE>() ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<EVE_VALUE>(), eve::Zero<EVE_TYPE>() ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::Allbits<EVE_TYPE>() , eve::Zero<EVE_VALUE>()), mask );

  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<EVE_TYPE>()  , eve::Zero<EVE_TYPE>() ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<EVE_VALUE>() , eve::Zero<EVE_TYPE>() ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::Allbits<EVE_TYPE>()  , eve::Zero<EVE_VALUE>()), mask);
}
