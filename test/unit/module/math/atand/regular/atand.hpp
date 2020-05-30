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

TTS_CASE_TPL("Check eve::atand return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atand(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::atand behavior", EVE_TYPE)
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atand(eve::Nan<T>()), (eve::Nan<T>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atand(eve::Inf<T>()) , (T( 90.)), 0.5);
    TTS_ULP_EQUAL(eve::atand(eve::Minf<T>()), (T(-90.)), 0.5);
  }

  TTS_ULP_EQUAL(eve::atand(T(0.5))  , (eve::radindeg(T(4.636476090008061e-01)))  , 0.5);
  TTS_ULP_EQUAL(eve::atand(T(-0.5)) , (eve::radindeg(T(-4.636476090008061e-01))) , 0.5);
  TTS_ULP_EQUAL(eve::atand(T(-1.))  , (T(-45))                                , 0.5);
  TTS_ULP_EQUAL(eve::atand(T(1.))   , (T(45))                                 , 0.5);
  TTS_ULP_EQUAL(eve::atand(T(0.))   , (T(0))                                  , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atand((T(0)))))          );
  TTS_EXPECT(all(eve::is_negative(eve::atand(T(-0.)))) );
}
