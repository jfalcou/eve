//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/factorials.hpp>
#include <eve/function/double_factorial.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::double_factorial return type", EVE_TYPE)
{
  if constexpr(eve::simd_value<T>)
  {
    using r_t = eve::wide<double, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::double_factorial(T()), r_t);
  }
  else
  {
    TTS_EXPR_IS(eve::double_factorial(T()), double);
  }
}

TTS_CASE_TPL("Check eve::double_factorial behavior", EVE_TYPE)
{
  using r_t = std::conditional_t<eve::simd_value<T>
    , eve::wide<double, eve::cardinal_t<T>>
   , double>;
  TTS_ULP_EQUAL(eve::double_factorial(T(10)) , r_t(boost::math::double_factorial<double>(10)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T( 5)) , r_t(boost::math::double_factorial<double>( 5)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T(180))    , r_t(boost::math::double_factorial<double>( 180)), 1.0);
  TTS_ULP_EQUAL(eve::double_factorial(T(181))    , r_t(boost::math::double_factorial<double>( 181)), 1.0);
  if constexpr(sizeof(eve::element_type_t<T>) > 1)
  {
    TTS_ULP_EQUAL(eve::double_factorial(T(300))    , r_t(boost::math::double_factorial<double>( 300)), 1.0);
    TTS_ULP_EQUAL(eve::double_factorial(T(301))    , eve::inf(eve::as<r_t>()), 0);
    TTS_ULP_EQUAL(eve::double_factorial(T(302))    , eve::inf(eve::as<r_t>()), 0);
  }
}
