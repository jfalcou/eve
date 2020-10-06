//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshr.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE("Check eve::rshr return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  TTS_EXPR_IS(eve::rshr(EVE_TYPE(), EVE_TYPE()), EVE_TYPE );
  TTS_EXPR_IS(eve::rshr(EVE_TYPE(), i_t()     ), EVE_TYPE );
  TTS_EXPR_IS(eve::rshr(EVE_TYPE(), u_t()     ), EVE_TYPE );
  TTS_EXPR_IS(eve::rshr(i_t()     , EVE_TYPE()), i_t      );
  TTS_EXPR_IS(eve::rshr(u_t()     , EVE_TYPE()), u_t      );
}

TTS_CASE("Check eve::rshr behavior")
{
  TTS_EQUAL(eve::rshr(EVE_TYPE(8), EVE_TYPE(2)), EVE_TYPE(2));

  TTS_EQUAL(eve::rshr(EVE_TYPE(1), -4), EVE_TYPE(16) );
  TTS_EQUAL(eve::rshr(EVE_TYPE(3),  1), EVE_TYPE( 1) );
  TTS_EQUAL(eve::rshr(EVE_TYPE(0), -3), EVE_TYPE( 0) );
  TTS_EQUAL(eve::rshr(EVE_TYPE(8),  2), EVE_TYPE( 2) );

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<EVE_TYPE>()), -1), EVE_TYPE(-2)             );
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<EVE_TYPE>()),  1), eve::allbits(eve::as<EVE_TYPE>()) );
  }
  else
  {
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<EVE_TYPE>()), -1), eve::allbits(eve::as<EVE_TYPE>()) - 1 );
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<EVE_TYPE>()),  1), eve::allbits(eve::as<EVE_TYPE>())/2   );
  }
}
