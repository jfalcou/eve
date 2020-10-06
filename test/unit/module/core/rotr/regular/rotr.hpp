//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rotr.hpp>
#include <eve/constant/allbits.hpp>
#include <bit>

TTS_CASE("Check eve::rotr return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  TTS_EXPR_IS(eve::rotr(EVE_TYPE(), EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS(eve::rotr(EVE_TYPE(), i_t()     ) , EVE_TYPE);
  TTS_EXPR_IS(eve::rotr(EVE_TYPE(), u_t()     ) , EVE_TYPE);
}

TTS_CASE("Check eve::rotr behavior")
{
  using ui_t  = eve::detail::as_integer_t<EVE_VALUE, unsigned>;
  auto alls   = eve::allbits(eve::as<EVE_TYPE>());
  auto allu   = eve::allbits(eve::as<ui_t>());

  TTS_EQUAL(eve::rotr(EVE_TYPE(0) ,  7) , EVE_TYPE(std::rotr(ui_t(0),  7)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(1) ,  4) , EVE_TYPE(std::rotr(ui_t(1),  4)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(3) ,  2) , EVE_TYPE(std::rotr(ui_t(3),  2)) );
  TTS_EQUAL(eve::rotr(alls        ,  1) , EVE_TYPE(std::rotr(allu   ,  1)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(0) , -7) , EVE_TYPE(std::rotr(ui_t(0), -7)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(1) , -4) , EVE_TYPE(std::rotr(ui_t(1), -4)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(3) , -2) , EVE_TYPE(std::rotr(ui_t(3), -2)) );

  TTS_EQUAL(eve::rotr(EVE_TYPE(0) , EVE_TYPE(7)) , EVE_TYPE(std::rotr(ui_t(0) ,  7)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(1) , EVE_TYPE(4)) , EVE_TYPE(std::rotr(ui_t(1) ,  4)) );
  TTS_EQUAL(eve::rotr(EVE_TYPE(3) , EVE_TYPE(2)) , EVE_TYPE(std::rotr(ui_t(3) ,  2)) );
  TTS_EQUAL(eve::rotr(alls        , EVE_TYPE(1)) , EVE_TYPE(std::rotr(allu    ,  1)) );
}
