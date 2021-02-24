//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/zeta.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::zeta return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::zeta(T(0)), T);
}

TTS_CASE_TPL("Check eve::zeta behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::zeta(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::inf(eve::as<T>())) , eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::zeta(T(1))   , eve::nan(eve::as<T>()));
   using v_t = eve::element_type_t<T>;
   TTS_ULP_EQUAL(eve::zeta(T(0))    , T(boost::math::zeta(v_t(0))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(-0.0))   ,T(boost::math::zeta(v_t(-0.0))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(1.5))    , T(boost::math::zeta(v_t(1.5))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(-1.5))   ,T(boost::math::zeta(v_t(-1.5))), 2.0);
   TTS_ULP_EQUAL(eve::zeta(T(14))    , T(boost::math::zeta(v_t(14))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(-14))   ,T(boost::math::zeta(v_t(-14))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(14.5))    , T(boost::math::zeta(v_t(14.5))), 0.5);
   TTS_ULP_EQUAL(eve::zeta(T(-14.5))   ,T(boost::math::zeta(v_t(-14.5))), 1.5);
}
