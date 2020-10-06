//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check hypot return type")
{
  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_TYPE(0))  , EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_VALUE(0), EVE_TYPE(0))  , EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_VALUE(0)) , EVE_TYPE);

  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_TYPE(0) , EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_TYPE(0) , EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_VALUE(0), EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_TYPE(0) , EVE_VALUE(0), EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_VALUE(0), EVE_TYPE(0) , EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_VALUE(0), EVE_TYPE(0) , EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::hypot( EVE_VALUE(0), EVE_VALUE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::hypot behavior")
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::hypot(eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::hypot(eve::inf(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
  }

  TTS_IEEE_EQUAL(eve::hypot(eve::valmax(eve::as<EVE_TYPE>()) , EVE_TYPE(0)            ) , eve::inf(eve::as<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::hypot(EVE_TYPE(0)             , eve::valmax(eve::as<EVE_TYPE>())) , eve::inf(eve::as<EVE_TYPE>()));

  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE(-1), EVE_TYPE(-1))                      , eve::sqrt_2(eve::as<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE( 1), EVE_TYPE( 1))                      , eve::sqrt_2(eve::as<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE( 0), EVE_TYPE( 0))                      , EVE_TYPE(0)            , 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::sqrt_2(eve::as<EVE_TYPE>()), eve::sqrt_2(eve::as<EVE_TYPE>())), EVE_TYPE(2)            , 0.5);
}

TTS_CASE("Check 3 params eve::hypot behavior")
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::hypot(eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::hypot(eve::inf(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
  }

  TTS_IEEE_EQUAL(eve::hypot(eve::valmax(eve::as<EVE_TYPE>()) , EVE_TYPE(0)            , EVE_TYPE(0)) , eve::inf(eve::as<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::hypot(EVE_TYPE(0)             , eve::valmax(eve::as<EVE_TYPE>()), EVE_TYPE(0)) , eve::inf(eve::as<EVE_TYPE>()));

  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE(-1), EVE_TYPE(-1), eve::sqrt_2(eve::as<EVE_TYPE>()) ) , EVE_TYPE(2)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE( 1), EVE_TYPE( 1), eve::sqrt_2(eve::as<EVE_TYPE>()) ) , EVE_TYPE(2)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE( 0), EVE_TYPE( 0), EVE_TYPE( 0)            ) , EVE_TYPE(0)                , 0.5);
  TTS_ULP_EQUAL(eve::hypot(EVE_TYPE( 1), EVE_TYPE( 1), EVE_TYPE( 1)            ) , EVE_TYPE(std::sqrt(EVE_VALUE(3))), 0.5);
}
