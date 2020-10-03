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
#include <eve/function/prev.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::small(eve::csc) return type")
{
  TTS_EXPR_IS(eve::small(eve::csc)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::small(eve::csc) behavior")
{
  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small(eve::csc)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::small(eve::csc)(EVE_TYPE( 0 )), EVE_TYPE(ref_csc(EVE_VALUE(0.0))));
  TTS_IEEE_EQUAL(eve::small(eve::csc)(EVE_TYPE(-0.)), EVE_TYPE(ref_csc(EVE_VALUE(-0.0))));

  TTS_ULP_EQUAL(eve::small(eve::csc)( EVE_TYPE(1)              ), EVE_TYPE(ref_csc(1.0))                   , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-EVE_TYPE(1)              ), EVE_TYPE(ref_csc(-1.0))                  , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_2(eve::as<EVE_TYPE>())   ), EVE_TYPE(ref_csc(-eve::pio_2(eve::as<EVE_VALUE>())))    , 1.0 );
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_4(eve::as<EVE_TYPE>())   ), EVE_TYPE(ref_csc(-eve::pio_4(eve::as<EVE_VALUE>())))    , 0.75);
  TTS_ULP_EQUAL(eve::small(eve::csc)(-eve::pio_4(eve::as<EVE_TYPE>())/ 2), EVE_TYPE(ref_csc(-eve::pio_4(eve::as<EVE_VALUE>())/2))  , 0.5 );
  TTS_ULP_EQUAL(eve::small(eve::csc)( eve::pio_4(eve::as<EVE_TYPE>())   ), EVE_TYPE(ref_csc(eve::pio_4(eve::as<EVE_VALUE>())))     , 0.5 );
  TTS_ULP_EQUAL(eve::small(eve::csc)( eve::pio_4(eve::as<EVE_TYPE>())/ 2), EVE_TYPE(ref_csc(eve::pio_4(eve::as<EVE_VALUE>())/2))   , 0.75);
  TTS_ULP_EQUAL(eve::small(eve::csc)(eve::pio_2(eve::as<EVE_TYPE>())    ), EVE_TYPE(ref_csc(eve::pio_2(eve::as<EVE_VALUE>())))     , 1.0 );

  auto z = eve::pio_2(eve::as<EVE_VALUE>());
  TTS_ULP_EQUAL(eve::small(eve::csc)(EVE_TYPE(z)), EVE_TYPE(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(EVE_TYPE(z)), EVE_TYPE(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(EVE_TYPE(z)), EVE_TYPE(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small(eve::csc)(EVE_TYPE(z)), EVE_TYPE(ref_csc(z)), 0.5);
}
