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
#include <eve/function/raw.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check raw(eve::acospi) return type")
{
  TTS_EXPR_IS(eve::raw_(eve::acospi)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check raw(eve::acospi) behavior")
{
  using eve::all;
  using eve::radinpi;
  using eve::raw_;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(2)), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(-2)), eve::Nan<EVE_TYPE>(), 0);
  }

  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(0.5)), EVE_TYPE(1 / 3.), 0.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(-0.5)), EVE_TYPE(2 / 3.), 0.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(-1.)), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(1.)), EVE_TYPE(0), 0);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(0.)), EVE_TYPE(0.5), 0.5);

  TTS_EXPECT(all(eve::is_positive(raw_(eve::acospi)(EVE_TYPE(1.)))));

  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(8.414715528e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(8.414715528e-01)))),
                2.0);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.689134359e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.689134359e-01)))),
                4.0);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.922192097e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.922192097e-01)))),
                7.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.995127916e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.995127916e-01)))),
                26.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.998779893e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.998779893e-01)))),
                44.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.999695420e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.999695420e-01)))),
                142);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.999927878e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.999927878e-01)))),
                234);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.999984503e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.999984503e-01)))),
                361.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.999996424e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.999996424e-01)))),
                867.5);
  TTS_ULP_EQUAL(raw_(eve::acospi)(EVE_TYPE(9.999999404e-01)),
                EVE_TYPE(radinpi(std::acos(EVE_VALUE(9.999999404e-01)))),
                2081.0);
}
