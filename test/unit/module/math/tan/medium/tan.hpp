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

TTS_CASE_TPL("Check eve::medium(eve::tan) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::medium(eve::tan)(T(0)), T);
}

TTS_CASE_TPL("Check eve::medium(eve::tan) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  using v_t = eve::element_type_t<T>;
  auto vpi_4 = eve::pio_4(eve::as<T>());
  auto spi_4 = eve::pio_4(eve::as<v_t>());

  TTS_IEEE_EQUAL( eve::medium(eve::tan)(T(-0.)), T(0));
  TTS_IEEE_EQUAL( eve::medium(eve::tan)(T(0))  , T(0));

  TTS_EXPECT(eve::all(eve::is_positive(eve::medium(eve::tan)(T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium(eve::tan)(T(-0.)))));

  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(1))        , T(std::tan(1.0))            , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(-1))       , T(std::tan(-1.0))           , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)( vpi_4)      , T(std::tan( spi_4))         , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(-vpi_4)      , T(std::tan(-spi_4))         , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(100.0))    , T(std::tan(v_t(100.0)))     , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(-100.0))   , T(std::tan(v_t(-100.0)))    , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(100000.0)) , T(std::tan(v_t(100000.0)))  , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(T(-100000.0)), T(std::tan(v_t(-100000.0))) , 0.5);
}

