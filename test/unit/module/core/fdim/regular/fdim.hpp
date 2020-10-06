//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fdim.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>

TTS_CASE("Check eve::fdim return type")
{
  TTS_EXPR_IS(eve::fdim(EVE_TYPE(), EVE_TYPE()), EVE_TYPE);
}

TTS_CASE(" fdim behaviour")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::fdim(eve::inf(eve::as<EVE_TYPE>()) , eve::inf(eve::as<EVE_TYPE>()))  , EVE_TYPE(0));
    TTS_EQUAL(eve::fdim(eve::minf(eve::as<EVE_TYPE>()), eve::minf(eve::as<EVE_TYPE>())) , EVE_TYPE(0));

    TTS_ULP_EQUAL(eve::fdim(eve::nan(eve::as<EVE_TYPE>()) , eve::nan(eve::as<EVE_TYPE>()) ), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::nan(eve::as<EVE_TYPE>()) , EVE_TYPE(0)          ), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::fdim(EVE_TYPE(0)          , eve::nan(eve::as<EVE_TYPE>()) ), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::nan(eve::as<EVE_TYPE>()) , EVE_TYPE(0)          ), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::fdim(EVE_TYPE(1)          , eve::nan(eve::as<EVE_TYPE>()) ), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::nan(eve::as<EVE_TYPE>()) , EVE_TYPE(1)          ), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_EQUAL(eve::fdim(EVE_TYPE(-1), EVE_TYPE(-1)) , EVE_TYPE(0));
  TTS_EQUAL(eve::fdim(EVE_TYPE( 1), EVE_TYPE( 1)) , EVE_TYPE(0));
  TTS_EQUAL(eve::fdim(EVE_TYPE( 0), EVE_TYPE( 0)) , EVE_TYPE(0));
  TTS_EQUAL(eve::fdim(EVE_TYPE( 1), EVE_TYPE( 0)) , EVE_TYPE(1));
  TTS_EQUAL(eve::fdim(EVE_TYPE( 2), EVE_TYPE(-3)) , EVE_TYPE(5));
  TTS_EQUAL(eve::fdim(EVE_TYPE( 2), EVE_TYPE( 3)) , EVE_TYPE(0));
}
