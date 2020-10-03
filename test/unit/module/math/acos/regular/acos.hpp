//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check acos return type")
{
  TTS_EXPR_IS(eve::acos(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::acos behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acos(EVE_TYPE(2)) , eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::acos(EVE_TYPE(-2)), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(eve::acos(EVE_TYPE( 0.5)) , eve::pi(eve::as<EVE_TYPE>())/3   , 0.5 );
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(-0.5)) , 2*eve::pi(eve::as<EVE_TYPE>())/3 , 0.5 );
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(-1. )) , eve::pi(eve::as<EVE_TYPE>())     , 0   );
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE( 1. )) , EVE_TYPE(0)             , 0   );
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE( 0. )) , eve::pio_2(eve::as<EVE_TYPE>())  , 0   );

  TTS_EXPECT( all(eve::is_positive(eve::acos(EVE_TYPE(1)))) );

  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(8.414715528e-01)), EVE_TYPE(std::acos(EVE_VALUE(8.414715528e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.689134359e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.689134359e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.922192097e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.922192097e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.995127916e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.995127916e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.998779893e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.998779893e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.999695420e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.999695420e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.999927878e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.999927878e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.999984503e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.999984503e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.999996424e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.999996424e-01))), 1);
  TTS_ULP_EQUAL(eve::acos(EVE_TYPE(9.999999404e-01)), EVE_TYPE(std::acos(EVE_VALUE(9.999999404e-01))), 1);
}
