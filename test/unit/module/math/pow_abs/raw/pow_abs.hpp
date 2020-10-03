//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::raw(eve::pow_abs) return type")
{
  TTS_EXPR_IS(eve::raw(eve::pow_abs)(EVE_TYPE(0)  , EVE_TYPE(0) ), EVE_TYPE);
  TTS_EXPR_IS(eve::raw(eve::pow_abs)(EVE_TYPE(0)  , EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::raw(eve::pow_abs)(EVE_VALUE(0) , EVE_TYPE(0) ), EVE_TYPE);
}

TTS_CASE("Check eve::raw(eve::pow_abs) behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(eve::minf(eve::as<EVE_TYPE>()), eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(0) );

    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(eve::inf(eve::as<EVE_TYPE>()) , EVE_TYPE(-0.5)       ), EVE_TYPE(0)         );
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(eve::inf(eve::as<EVE_TYPE>()) , EVE_TYPE(0.5)        ), eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(eve::inf(eve::as<EVE_TYPE>()) , eve::inf(eve::as<EVE_TYPE>()) ), eve::inf(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(eve::nan(eve::as<EVE_TYPE>()) , eve::nan(eve::as<EVE_TYPE>()) ), eve::nan(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0)  , EVE_TYPE(-1)         ), eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0)  , EVE_TYPE(-2)         ), eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0.5), eve::inf(eve::as<EVE_TYPE>()) ), EVE_TYPE(0)         );
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0.5), eve::minf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(2)  , eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(0)         );
    TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(2)  , eve::inf(eve::as<EVE_TYPE>()) ), eve::inf(eve::as<EVE_TYPE>()));
  }

  TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(-1)  , EVE_TYPE(-1))  , EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE( 1)  , EVE_TYPE( 1))  , EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(-1)  , EVE_TYPE( 5))  , EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(-1)  , EVE_TYPE( 6))  , EVE_TYPE(1));
  TTS_ULP_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0.5) , EVE_TYPE(0.25)), EVE_TYPE(0.840896415253715)            , 2);
  TTS_ULP_EQUAL(eve::raw(eve::pow_abs)(EVE_TYPE(0.5) , EVE_TYPE(0.25)), EVE_TYPE(std::pow(EVE_VALUE(0.5), EVE_VALUE(0.25))), 2);
}
