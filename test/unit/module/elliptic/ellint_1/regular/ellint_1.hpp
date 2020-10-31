//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_1.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::ellint_1 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::ellint_1(T(0)), T);
}

TTS_CASE_TPL("Check eve::ellint_1 behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::ellint_1(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::ellint_1(T(1)) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::ellint_1(T(-1)), eve::inf(eve::as<T>()) );
  }

  TTS_ULP_EQUAL( eve::ellint_1(T( 0.)), T(boost::math::ellint_1(v_t(0))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_1(T( 0.5)), T(boost::math::ellint_1(v_t(0.5))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_1(T( 0.9)), T(boost::math::ellint_1(v_t(0.9))), 0.5);

}
