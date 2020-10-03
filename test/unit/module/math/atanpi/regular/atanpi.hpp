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


TTS_CASE("Check eve::atanpi return type")
{
  TTS_EXPR_IS(eve::atanpi(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::atanpi behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::nan(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::inf(eve::as<EVE_TYPE>())) , EVE_TYPE( 0.5) );
    TTS_IEEE_EQUAL(eve::atanpi(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(-0.5) );
  }

  TTS_ULP_EQUAL(eve::atanpi(EVE_TYPE(0.5))  , (eve::radinpi(EVE_TYPE(4.636476090008061e-01))) , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(EVE_TYPE(-0.5)) , (eve::radinpi(EVE_TYPE(-4.636476090008061e-01))), 0.5);
  TTS_ULP_EQUAL(eve::atanpi(EVE_TYPE(-1.))  , -EVE_TYPE(0.25)                                 , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(EVE_TYPE(1.))   ,  EVE_TYPE(0.25)                                 , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(EVE_TYPE(0.))   ,  EVE_TYPE(0)                                    , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atanpi((EVE_TYPE(0)))))  );
  TTS_EXPECT(all(eve::is_negative(eve::atanpi(EVE_TYPE(-0.)))) );
}
