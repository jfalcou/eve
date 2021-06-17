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
#include <eve/function/bernouilli.hpp>
#include <eve/function/converter.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::bernouilli"
              , eve::test::simd::unsigned_integers)
<typename T>(eve::as_<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::bernouilli(T())                       , d_t);
  TTS_EXPR_IS( eve::bernouilli(v_t())                     , double );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::bernouilli on wide"
        , eve::test::simd::unsigned_integers

         )
  <typename T>(eve::as_<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::bernouilli(T(10)) , d_t(5.0/66));
  TTS_EQUAL(eve::bernouilli(T(4))  , d_t(-1.0/30));
  TTS_EQUAL(eve::bernouilli(T(0))  , d_t(1));
  TTS_EQUAL(eve::bernouilli(T(1))  , d_t(-0.5));
};
