//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::restricted_(eve::tan) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::tan)(T(0)), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::tan) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::tan)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tan)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tan)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  using v_t = eve::element_type_t<T>;

  TTS_IEEE_EQUAL(eve::restricted_(eve::tan)(T( 0 )), T(0) );
  TTS_IEEE_EQUAL(eve::restricted_(eve::tan)(T(-0.)), T(0) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::tan)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::tan)(T( 0 )))));

  auto vpi_4 = eve::pio_4(eve::as<T>());
  auto spi_4 = eve::pio_4(eve::as<v_t>());

  TTS_ULP_EQUAL( eve::restricted_(eve::tan)(T(1))     , eve::nan(eve::as<T>())         , 0.5 );
  TTS_ULP_EQUAL( eve::restricted_(eve::tan)(T(-1))    , eve::nan(eve::as<T>())         , 0.5 );
  TTS_ULP_EQUAL( eve::restricted_(eve::tan)( vpi_4)   , T(std::tan( spi_4)   ), 0.5 );
  TTS_ULP_EQUAL( eve::restricted_(eve::tan)(-vpi_4)   , T(std::tan(-spi_4)   ), 0.5 );
  TTS_ULP_EQUAL( eve::restricted_(eve::tan)( vpi_4/2) , T(std::tan( spi_4/2) ), 0.5 );
  TTS_ULP_EQUAL( eve::restricted_(eve::tan)(-vpi_4/2) , T(std::tan(-spi_4/2) ), 0.5 );
}
