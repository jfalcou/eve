//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/all.hpp>
#include <eve/function/raw.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::raw_(eve::acosd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw_(eve::acosd)(T(0)), T);
}

TTS_CASE_TPL("Check eve::raw_(eve::acosd) behavior", EVE_TYPE)
{
  using eve::all;
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(2)) , eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(-2)), eve::Nan<T>(), 0);
  }

  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T( 0.5)), T(60)  , 0.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(-0.5)), T(120) , 0.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(-1. )), T(180) , 0.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T( 1. )), T(0)   , 0  );
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T( 0. )), T(90)  , 0.5);

  TTS_EXPECT( all(eve::is_positive(eve::raw_(eve::acosd)(T(1.)))) );

  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(8.414715528e-01)), T(eve::radindeg(std::acos(v_t(8.414715528e-01)))), 1.5 );
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.689134359e-01)), T(eve::radindeg(std::acos(v_t(9.689134359e-01)))), 4.0 );
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.922192097e-01)), T(eve::radindeg(std::acos(v_t(9.922192097e-01)))), 7.5 );
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.995127916e-01)), T(eve::radindeg(std::acos(v_t(9.995127916e-01)))), 33.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.998779893e-01)), T(eve::radindeg(std::acos(v_t(9.998779893e-01)))), 44.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.999695420e-01)), T(eve::radindeg(std::acos(v_t(9.999695420e-01)))), 142);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.999927878e-01)), T(eve::radindeg(std::acos(v_t(9.999927878e-01)))), 234 );
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.999984503e-01)), T(eve::radindeg(std::acos(v_t(9.999984503e-01)))), 361.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.999996424e-01)), T(eve::radindeg(std::acos(v_t(9.999996424e-01)))), 867.5);
  TTS_ULP_EQUAL(eve::raw_(eve::acosd)(T(9.999999404e-01)), T(eve::radindeg(std::acos(v_t(9.999999404e-01)))), 1643.5);
}
