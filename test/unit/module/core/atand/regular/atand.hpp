//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/atand.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::atand return type") { TTS_EXPR_IS(eve::atand(EVE_TYPE(0)), (EVE_TYPE)); }

TTS_CASE("Check eve::eve::atand behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atand(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atand(eve::Inf<EVE_TYPE>()), (EVE_TYPE(90.)), 0.5);
    TTS_ULP_EQUAL(eve::atand(eve::Minf<EVE_TYPE>()), (EVE_TYPE(-90.)), 0.5);
  }

  TTS_ULP_EQUAL(eve::atand(EVE_TYPE(0.5)), (eve::radindeg(EVE_TYPE(4.636476090008061e-01))), 0.5);
  TTS_ULP_EQUAL(eve::atand(EVE_TYPE(-0.5)), (eve::radindeg(EVE_TYPE(-4.636476090008061e-01))), 0.5);
  TTS_ULP_EQUAL(eve::atand(EVE_TYPE(-1.)), (EVE_TYPE(-45)), 0.5);
  TTS_ULP_EQUAL(eve::atand(EVE_TYPE(1.)), (EVE_TYPE(45)), 0.5);
  TTS_ULP_EQUAL(eve::atand(EVE_TYPE(0.)), (EVE_TYPE(0)), 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atand((EVE_TYPE(0))))));
  TTS_EXPECT(all(eve::is_negative(eve::atand(eve::Mzero<EVE_TYPE>()))));
}
