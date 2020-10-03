//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted(eve::cot) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::cot)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::eve::restricted(eve::cot) behavior")
{

  auto ref_cot =  [](auto x) { return eve::rec(std::tan(double(x))); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::cot)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cot)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cot)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::cot)(EVE_TYPE( 0 )) , eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cot)(EVE_TYPE(-0.)) , eve::minf(eve::as<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::restricted(eve::cot)( EVE_TYPE(1 )) , eve::nan(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cot)(-EVE_TYPE(1 )) , eve::nan(eve::as<EVE_TYPE>()) );

  TTS_ULP_EQUAL(eve::restricted(eve::cot)( eve::pio_4(eve::as<EVE_TYPE>()))  , EVE_TYPE(ref_cot( eve::pio_4(eve::as<EVE_VALUE>()))), 1  );
  TTS_ULP_EQUAL(eve::restricted(eve::cot)(-eve::pio_4(eve::as<EVE_TYPE>()))  , EVE_TYPE(ref_cot(-eve::pio_4(eve::as<EVE_VALUE>()))), 1  );
  TTS_ULP_EQUAL(eve::restricted(eve::cot)( eve::pio_4(eve::as<EVE_TYPE>())/2), EVE_TYPE(ref_cot( eve::pio_4(eve::as<EVE_VALUE>())/2)), 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::cot)(-eve::pio_4(eve::as<EVE_TYPE>())/2), EVE_TYPE(ref_cot(-eve::pio_4(eve::as<EVE_VALUE>())/2)), 0.5);
}
