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

TTS_CASE_TPL("Check eve::rshr return type", EVE_TYPE)
{
  using i_t = eve::as_integer_t<T, signed>;
  using u_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::rshr(  T(),  T()),   T);
  TTS_EXPR_IS(eve::rshr(  T(),i_t()),   T);
  TTS_EXPR_IS(eve::rshr(  T(),u_t()),   T);
  TTS_EXPR_IS(eve::rshr(i_t(),  T()), i_t);
  TTS_EXPR_IS(eve::rshr(u_t(),  T()), u_t);
}

TTS_CASE_TPL("Check eve::rshr behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::rshr(T(8), T(2)), T(2));

  TTS_EQUAL(eve::rshr(T(1), -4), T(16) );
  TTS_EQUAL(eve::rshr(T(3),  1), T( 1) );
  TTS_EQUAL(eve::rshr(T(0), -3), T( 0) );
  TTS_EQUAL(eve::rshr(T(8),  2), T( 2) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<T>()), -1), T(-2)             );
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<T>()),  1), eve::allbits(eve::as<T>()) );
  }
  else
  {
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<T>()), -1), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL(eve::rshr(eve::allbits(eve::as<T>()),  1), eve::allbits(eve::as<T>())/2   );
  }
}
