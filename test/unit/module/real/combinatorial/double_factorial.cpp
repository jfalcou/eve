//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/double_factorial.hpp>
#include <eve/function/converter.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::double_factorial"
              , eve::test::simd::unsigned_integers)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::double_factorial(T())                       , d_t);
  TTS_EXPR_IS( eve::double_factorial(v_t())                     , double );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::double_factorial on wide"
        , eve::test::simd::unsigned_integers
         )
  <typename T>(eve::as_<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_ULP_EQUAL(eve::double_factorial(T(10)) , d_t(boost::math::double_factorial<double>(10)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T( 5)) , d_t(boost::math::double_factorial<double>( 5)), 0.5);
  TTS_ULP_EQUAL(eve::double_factorial(T(180))    , d_t(boost::math::double_factorial<double>( 180)), 1.0);
  TTS_ULP_EQUAL(eve::double_factorial(T(181))    , d_t(boost::math::double_factorial<double>( 181)), 1.0);
  if constexpr(sizeof(eve::element_type_t<T>) > 1)
  {
    TTS_ULP_EQUAL(eve::double_factorial(T(300))    , d_t(boost::math::double_factorial<double>( 300)), 1.0);
    TTS_ULP_EQUAL(eve::double_factorial(T(301))    , eve::inf(eve::as<d_t>()), 0);
    TTS_ULP_EQUAL(eve::double_factorial(T(302))    , eve::inf(eve::as<d_t>()), 0);
  }
};
