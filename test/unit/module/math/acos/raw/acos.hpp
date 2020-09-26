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
#include <eve/function/raw.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check acos return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::acos)(T(0)), T);
}

TTS_CASE_TPL("Check raw(eve::acos) behavior", EVE_TYPE)
{
  using eve::raw;
  using eve::all;

  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(raw(eve::acos)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5 );
    TTS_ULP_EQUAL(raw(eve::acos)(T(2))          , eve::nan(eve::as<T>()), 0   );
    TTS_ULP_EQUAL(raw(eve::acos)(T(-2))         , eve::nan(eve::as<T>()), 0   );
  }

  TTS_ULP_EQUAL(raw(eve::acos)(T( 0.5)) , eve::pi(eve::as<T>())/3   , 0.5 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(-0.5)) , 2*eve::pi(eve::as<T>())/3 , 0.5 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(-1. )) , eve::pi(eve::as<T>())     , 0   );
  TTS_ULP_EQUAL(raw(eve::acos)(T( 1. )) , T(0)             , 0   );
  TTS_ULP_EQUAL(raw(eve::acos)(T( 0. )) , eve::pio_2(eve::as<T>())  , 0   );

  TTS_EXPECT( all(eve::is_positive(eve::acos(T(1)))) );

  TTS_ULP_EQUAL(raw(eve::acos)(T(8.414715528e-01)), T(std::acos(v_t(8.414715528e-01))), 1.5 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.689134359e-01)), T(std::acos(v_t(9.689134359e-01))), 4.0 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.922192097e-01)), T(std::acos(v_t(9.922192097e-01))), 7.5 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.995127916e-01)), T(std::acos(v_t(9.995127916e-01))), 32.5);
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.998779893e-01)), T(std::acos(v_t(9.998779893e-01))), 44.5);
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.999695420e-01)), T(std::acos(v_t(9.999695420e-01))), 142);
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.999927878e-01)), T(std::acos(v_t(9.999927878e-01))), 234 );
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.999984503e-01)), T(std::acos(v_t(9.999984503e-01))), 361.5);
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.999996424e-01)), T(std::acos(v_t(9.999996424e-01))), 867.5);
  TTS_ULP_EQUAL(raw(eve::acos)(T(9.999999404e-01)), T(std::acos(v_t(9.999999404e-01))), 1643.5);
}
