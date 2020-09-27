//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/beta.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::beta return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::beta(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::beta behavior", EVE_TYPE)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::beta(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(eve::inf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(T(1), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(eve::minf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(T(1), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);

    TTS_ULP_EQUAL(eve::beta(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(eve::nan(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(eve::beta(T(1), eve::nan(eve::as<T>())), eve::nan(as<T>()), 0);
  }


  TTS_ULP_EQUAL(eve::beta(T(-0.0), T(-0.0)), T(std::beta(elt_t(-0.0), elt_t(-0.0))), 0);
  TTS_ULP_EQUAL(eve::beta(T( 0.0), T( 0.0)), T(std::beta(elt_t(0.0), elt_t(0.0))), 0);
  TTS_ULP_EQUAL(eve::beta(T( 1.0), T( 1.0)), T(std::beta(elt_t(1.0), elt_t(1.0))), 0);
  TTS_ULP_EQUAL(eve::beta(T( 2.0), T( 3.0)), T(std::beta(elt_t(2.0), elt_t(3.0))), 0);
  TTS_ULP_EQUAL(eve::beta(T( 2.5), T( 3.7)), T(std::beta(elt_t(2.5), elt_t(3.7))), 0);

}
