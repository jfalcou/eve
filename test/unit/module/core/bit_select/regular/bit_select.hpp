//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

TTS_CASE_TPL("Check eve::bit_select return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::bit_select(  T() ,   T() ,   T() ), T);
  TTS_EXPR_IS(eve::bit_select(  T() ,   T() , v_t() ), T);
  TTS_EXPR_IS(eve::bit_select(  T() , v_t() ,   T() ), T);
  TTS_EXPR_IS(eve::bit_select(i_t() ,   T() ,   T() ), T);
  TTS_EXPR_IS(eve::bit_select(i_t() ,   T() , v_t() ), T);
  TTS_EXPR_IS(eve::bit_select(i_t() , v_t() ,   T() ), T);

  TTS_EXPR_IS(eve::bit_select(eve::logical<T>(),  T() ,   T() ), T);
  TTS_EXPR_IS(eve::bit_select(eve::logical<T>(),  T() , v_t() ), T);
  TTS_EXPR_IS(eve::bit_select(eve::logical<T>(),v_t() ,   T() ), T);
}

TTS_CASE_TPL( "Check eve::bit_select behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::detail::as_integer_t<T, unsigned>;
  using vi_t = eve::detail::as_integer_t<v_t, unsigned>;
  using v_t =  eve::element_type_t<T>;

  std::uint64_t base  = 0xF5555552F552F5F2ULL;
  i_t           imask = static_cast<i_t>(base & std::uint64_t(~vi_t(0)));
  T          mask  = eve::bit_cast(imask, eve::as(T()));

  TTS_EQUAL( eve::bit_select( imask, eve::allbits(eve::as<T>()) , T( 0 ) ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::allbits(eve::as<v_t>()), T( 0 ) ), mask );
  TTS_EQUAL( eve::bit_select( imask, eve::allbits(eve::as<T>()) , eve::zero(eve::as<v_t>())), mask );

  TTS_EQUAL( eve::bit_select( mask, eve::allbits(eve::as<T>())  , T( 0 ) ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::allbits(eve::as<v_t>()) , T( 0 ) ), mask);
  TTS_EQUAL( eve::bit_select( mask, eve::allbits(eve::as<T>())  , eve::zero(eve::as<v_t>())), mask);
}
