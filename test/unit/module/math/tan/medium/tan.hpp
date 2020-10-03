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

TTS_CASE("Check eve::medium(eve::tan) return type")
{
  TTS_EXPR_IS(eve::medium(eve::tan)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::medium(eve::tan) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::tan)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  auto vpi_4 = eve::pio_4(eve::as<EVE_TYPE>());
  auto spi_4 = eve::pio_4(eve::as<EVE_VALUE>());

  TTS_IEEE_EQUAL( eve::medium(eve::tan)(EVE_TYPE(-0.)), EVE_TYPE(0));
  TTS_IEEE_EQUAL( eve::medium(eve::tan)(EVE_TYPE(0))  , EVE_TYPE(0));

  TTS_EXPECT(eve::all(eve::is_positive(eve::medium(eve::tan)(EVE_TYPE( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium(eve::tan)(EVE_TYPE(-0.)))));

  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(1))        , EVE_TYPE(std::tan(1.0))            , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(-1))       , EVE_TYPE(std::tan(-1.0))           , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)( vpi_4)      , EVE_TYPE(std::tan( spi_4))         , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(-vpi_4)      , EVE_TYPE(std::tan(-spi_4))         , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(100.0))    , EVE_TYPE(std::tan(EVE_VALUE(100.0)))     , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(-100.0))   , EVE_TYPE(std::tan(EVE_VALUE(-100.0)))    , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(100000.0)) , EVE_TYPE(std::tan(EVE_VALUE(100000.0)))  , 0.5);
  TTS_ULP_EQUAL(eve::medium(eve::tan)(EVE_TYPE(-100000.0)), EVE_TYPE(std::tan(EVE_VALUE(-100000.0))) , 0.5);
}

