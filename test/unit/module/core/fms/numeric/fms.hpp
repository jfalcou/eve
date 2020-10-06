//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::numeric(eve::fms) return type")
{
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_TYPE()   , EVE_TYPE()   , EVE_TYPE()   ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_TYPE()   , EVE_TYPE()   , EVE_VALUE() ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_TYPE()   , EVE_VALUE() , EVE_TYPE()   ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_TYPE()   , EVE_VALUE() , EVE_VALUE() ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_VALUE() , EVE_TYPE()   , EVE_TYPE()   ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_VALUE() , EVE_TYPE()   , EVE_VALUE() ) , EVE_TYPE);
  TTS_EXPR_IS(eve::numeric(eve::fms)(EVE_VALUE() , EVE_VALUE() , EVE_TYPE()   ) , EVE_TYPE);
}

TTS_CASE("Check eve::numeric(eve::fms) behavior")
{
  TTS_EQUAL(eve::numeric(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE( 0)), EVE_TYPE( 0));
  TTS_EQUAL(eve::numeric(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(-7)), EVE_TYPE( 7));
  TTS_EQUAL(eve::numeric(eve::fms)(EVE_TYPE(2), EVE_TYPE(0), EVE_TYPE(-7)), EVE_TYPE( 7));
  TTS_EQUAL(eve::numeric(eve::fms)(EVE_TYPE(0), EVE_TYPE(5), EVE_TYPE(-7)), EVE_TYPE( 7));
  TTS_EQUAL(eve::numeric(eve::fms)(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(-7)), EVE_TYPE(17));

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    EVE_TYPE e = eve::eps(eve::as<EVE_TYPE>());
    TTS_EQUAL(eve::numeric(eve::fms)(eve::inc(e), eve::oneminus(e), EVE_TYPE(1)), -eve::sqr(e));
    TTS_EQUAL(eve::numeric(eve::fms)(eve::valmax(eve::as<EVE_TYPE>()), EVE_TYPE(2), eve::valmax(eve::as<EVE_TYPE>())), eve::valmax(eve::as<EVE_TYPE>()));
  }
}
