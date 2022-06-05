//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/special.hpp>
#include <cmath>




//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of betainc"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::betainc(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::betainc(T(), T(), v_t()), T);
  TTS_EXPR_IS( eve::betainc(v_t(), T(), T()), T);
  TTS_EXPR_IS( eve::betainc(T(), v_t(), T() ), T);
  TTS_EXPR_IS( eve::betainc(v_t(), T(), v_t()), T);
  TTS_EXPR_IS( eve::betainc(v_t(), v_t(), T()), T);
  TTS_EXPR_IS( eve::betainc(T(), v_t(), v_t()), T);
  TTS_EXPR_IS( eve::betainc(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// betainc  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of betainc on wide"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using eve::betainc;
  using eve::as;
  TTS_EQUAL(eve::betainc(T(0), T(0), T(0)), T(0)  );
  TTS_EQUAL(eve::betainc(T(0), T(0), T(7)), T(0)  );
  TTS_ULP_EQUAL(eve::betainc(T(0.5), T(0.5), T(0.5)), T(0.5) , 15 );
  TTS_ULP_EQUAL(eve::betainc(T(0.2), T(0.3), T(2)), T(7.651219897728122e-01), 30);
};
