//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::csc return type")
{
  TTS_EXPR_IS(eve::csc(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::csc behavior")
{
  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::csc(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::csc(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::csc(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::csc(EVE_TYPE( 0 )), EVE_TYPE(ref_csc(EVE_VALUE(0.0))));
  TTS_IEEE_EQUAL(eve::csc(EVE_TYPE(-0.)), EVE_TYPE(ref_csc(EVE_VALUE(-0.0))));

  TTS_ULP_EQUAL(eve::csc( EVE_TYPE(1)            ) , EVE_TYPE(ref_csc(1.0))               , 1.0 );
  TTS_ULP_EQUAL(eve::csc(-EVE_TYPE(1)            ) , EVE_TYPE(ref_csc(-1.0))              , 1.0 );
  TTS_ULP_EQUAL(eve::csc(-eve::pio_4(eve::as<EVE_TYPE>()) ) , EVE_TYPE(ref_csc(-eve::pio_4(eve::as<EVE_VALUE>()))), 0.75);
  TTS_ULP_EQUAL(eve::csc( eve::pio_4(eve::as<EVE_TYPE>()) ) , EVE_TYPE(ref_csc(eve::pio_4(eve::as<EVE_VALUE>()))) , 0.75);
  TTS_ULP_EQUAL(eve::csc( EVE_TYPE(100.0)        ) , EVE_TYPE(ref_csc(EVE_VALUE(100.0)))        , 1.5 );
  TTS_ULP_EQUAL(eve::csc(-EVE_TYPE(100.0)        ) , EVE_TYPE(ref_csc(EVE_VALUE(-100.0)))       , 1.5 );
  TTS_ULP_EQUAL(eve::csc( EVE_TYPE(100000.0)     ) , EVE_TYPE(ref_csc(EVE_VALUE(100000.0)))     , 0.5 );
  TTS_ULP_EQUAL(eve::csc(-EVE_TYPE(100000.0)     ) , EVE_TYPE(ref_csc(EVE_VALUE(-100000.0)))    , 0.5 );
  TTS_ULP_EQUAL(eve::csc( EVE_TYPE(1000000.0)    ) , EVE_TYPE(ref_csc(EVE_VALUE(1000000.0)))     , 0.5 );
  TTS_ULP_EQUAL(eve::csc(-EVE_TYPE(1000000.0)    ) , EVE_TYPE(ref_csc(EVE_VALUE(-1000000.0)))    , 0.5 );
}
