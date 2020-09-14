//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/nan.hpp>
#include <eve/function/acospi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::acospi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acospi(T(0)), T);
}

TTS_CASE_TPL("Check eve::acospi behavior", EVE_TYPE)
{
  using eve::all;
  using eve::radinpi;
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acospi(T(2)) , eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::acospi(T(-2)), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve::acospi(T( 0.5)), T(1/3.) , 0.5);
  TTS_ULP_EQUAL(eve::acospi(T(-0.5)), T(2/3.) , 0.5);
  TTS_ULP_EQUAL(eve::acospi(T(-1. )), T(1)    , 0.5);
  TTS_ULP_EQUAL(eve::acospi(T( 1. )), T(0)    , 0  );
  TTS_ULP_EQUAL(eve::acospi(T( 0. )), T(0.5)  , 0.5);

  TTS_EXPECT( all(eve::is_positive(eve::acospi(T(1.)))) );

  TTS_ULP_EQUAL(eve::acospi(T(8.414715528e-01)), T(radinpi(std::acos(v_t(8.414715528e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.689134359e-01)), T(radinpi(std::acos(v_t(9.689134359e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.922192097e-01)), T(radinpi(std::acos(v_t(9.922192097e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.995127916e-01)), T(radinpi(std::acos(v_t(9.995127916e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.998779893e-01)), T(radinpi(std::acos(v_t(9.998779893e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.999695420e-01)), T(radinpi(std::acos(v_t(9.999695420e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.999927878e-01)), T(radinpi(std::acos(v_t(9.999927878e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.999984503e-01)), T(radinpi(std::acos(v_t(9.999984503e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.999996424e-01)), T(radinpi(std::acos(v_t(9.999996424e-01)))), 1);
  TTS_ULP_EQUAL(eve::acospi(T(9.999999404e-01)), T(radinpi(std::acos(v_t(9.999999404e-01)))), 1);
}
