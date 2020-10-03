//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expx2.hpp>
#include <eve/function/exp.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

TTS_CASE("Check eve::expx2 return type")
{
  TTS_EXPR_IS(eve::expx2(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::expx2 behavior")
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(1)), eve::exp(EVE_TYPE(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(0)), EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(4)), eve::exp(EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-4)),eve::exp(EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<EVE_TYPE>())) , eve::nan(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<EVE_TYPE>())) , eve::inf(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<EVE_TYPE>())), eve::inf(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-0.)), EVE_TYPE(1));
  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(-1)) , eve::exp(EVE_TYPE(1)), 0.5);
}

TTS_CASE("Check eve::expx2 behavior")
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(1), EVE_TYPE(1)), eve::exp(EVE_TYPE(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(0), EVE_TYPE(1)), EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(4), EVE_TYPE(1)), eve::exp(EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-4), EVE_TYPE(1)),eve::exp(EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<EVE_TYPE>()), EVE_TYPE(1)) , eve::nan(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<EVE_TYPE>()), EVE_TYPE(1)) , eve::inf(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<EVE_TYPE>()), EVE_TYPE(1)), eve::inf(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-0.), EVE_TYPE(1)), EVE_TYPE(1));
  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(-1), EVE_TYPE(1)) , eve::exp(EVE_TYPE(1)), 0.5);

  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(1), EVE_TYPE(-1)), eve::exp(-EVE_TYPE(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(0), EVE_TYPE(-1)), EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(4), EVE_TYPE(-1)), eve::exp(-EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-4), EVE_TYPE(-1)),eve::exp(-EVE_TYPE(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<EVE_TYPE>()), EVE_TYPE(-1)) , eve::nan(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<EVE_TYPE>()), EVE_TYPE(-1)) , eve::zero(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<EVE_TYPE>()), EVE_TYPE(-1)), eve::zero(as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::expx2(EVE_TYPE(-0.), EVE_TYPE(-1)), EVE_TYPE(1));
  TTS_ULP_EQUAL (eve::expx2(EVE_TYPE(-1), EVE_TYPE(-1)) , eve::exp(-EVE_TYPE(1)), 0.5);
}
