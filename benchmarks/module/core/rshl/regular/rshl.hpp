//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshl.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::rshl return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  TTS_EXPR_IS(eve::rshl(EVE_TYPE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::rshl(EVE_TYPE(), i_t())  , (EVE_TYPE));
  TTS_EXPR_IS(eve::rshl(EVE_TYPE(), u_t())  , (EVE_TYPE));
  TTS_EXPR_IS(eve::rshl(i_t() , EVE_TYPE())  , i_t);
  TTS_EXPR_IS(eve::rshl(u_t() , EVE_TYPE())  , u_t);
}

TTS_CASE("Check eve::rshl behavior")
{
  TTS_EQUAL(eve::rshl((EVE_TYPE(1)), (EVE_TYPE(4))  ), (EVE_TYPE(16)));

  TTS_EQUAL(eve::rshl((EVE_TYPE(1)),  4         ), (EVE_TYPE(16)));
  TTS_EQUAL(eve::rshl((EVE_TYPE(3)), -1         ), (EVE_TYPE( 1)));
  TTS_EQUAL(eve::rshl((EVE_TYPE(0)),  3         ), (EVE_TYPE( 0)));
  TTS_EQUAL(eve::rshl((EVE_TYPE(8)), -2         ), (EVE_TYPE( 2)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::rshl(eve::Allbits<EVE_TYPE>(), 1), EVE_TYPE(-2));
    TTS_EQUAL(eve::rshl(eve::Allbits<EVE_TYPE>(), -1), eve::Allbits<EVE_TYPE>());
  }
  else
  {
    TTS_EQUAL(eve::rshl(eve::Allbits<EVE_TYPE>(), -1), eve::Allbits<EVE_TYPE>()/2 );
    TTS_EQUAL(eve::rshl(eve::Allbits<EVE_TYPE>(),  1), eve::Allbits<EVE_TYPE>() - 1 );
  }
}
