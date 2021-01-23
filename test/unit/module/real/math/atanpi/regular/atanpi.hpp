//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::atanpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atanpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::atanpi behavior", EVE_TYPE)
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::nan(eve::as<T>())), (eve::nan(eve::as<T>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::inf(eve::as<T>())) , T( 0.5) );
    TTS_IEEE_EQUAL(eve::atanpi(eve::minf(eve::as<T>())), T(-0.5) );
  }

  TTS_ULP_EQUAL(eve::atanpi(T(0.5))  , (eve::radinpi(T(4.636476090008061e-01))) , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(T(-0.5)) , (eve::radinpi(T(-4.636476090008061e-01))), 0.5);
  TTS_ULP_EQUAL(eve::atanpi(T(-1.))  , -T(0.25)                                 , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(T(1.))   ,  T(0.25)                                 , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(T(0.))   ,  T(0)                                    , 0.5);

  TTS_EXPECT(eve::all(eve::is_positive(eve::atanpi((T(0)))))  );
  TTS_EXPECT(eve::all(eve::is_negative(eve::atanpi(T(-0.)))) );
}
