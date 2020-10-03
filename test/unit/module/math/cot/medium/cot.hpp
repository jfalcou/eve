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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::medium(eve::cot) return type")
{
  TTS_EXPR_IS(eve::cot(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::medium(eve::cot) behavior")
{
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::inf(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::minf(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  TTS_ULP_EQUAL(eve::medium(eve::cot)(EVE_TYPE(1)), EVE_TYPE(my_stdcot(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::medium(eve::cot)(EVE_TYPE(-1)),EVE_TYPE(my_stdcot(-1.0)), 1.0);
  TTS_IEEE_EQUAL(eve::medium(eve::cot)(EVE_TYPE(0)), (eve::inf(eve::as<EVE_TYPE>())));
  TTS_IEEE_EQUAL(eve::medium(eve::cot)(EVE_TYPE(-0.)), (eve::minf(eve::as<EVE_TYPE>())));
  TTS_ULP_EQUAL((eve::medium(eve::cot)(eve::pio_4(eve::as<EVE_TYPE>()))), (EVE_TYPE(my_stdcot(eve::pio_4(eve::as<EVE_VALUE>())))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(-eve::pio_4(eve::as<EVE_TYPE>()))),(EVE_TYPE(my_stdcot(-eve::pio_4(eve::as<EVE_VALUE>())))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(EVE_TYPE(100.0))), EVE_TYPE(my_stdcot(EVE_VALUE(100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(EVE_TYPE(-100.0))),EVE_TYPE(my_stdcot(EVE_VALUE(-100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(EVE_TYPE(100000.0))), EVE_TYPE(my_stdcot(EVE_VALUE(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(EVE_TYPE(-100000.0))),EVE_TYPE(my_stdcot(EVE_VALUE(-100000.0))), 0.5);
}

