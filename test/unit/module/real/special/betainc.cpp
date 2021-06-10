//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/betainc.hpp>
#include <eve/function/diff/betainc.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/digamma.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <eve/detail/diff_div.hpp>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of betainc"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as_<T>)
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
  <typename T>(eve::as_<T>)
{
  using eve::betainc;
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::betainc(T(0), T(0), T(0)), T(0)  );
  TTS_EQUAL(eve::betainc(T(0), T(0), T(7)), T(0)  );
  TTS_ULP_EQUAL(eve::betainc(T(0.5), T(0.5), T(0.5)), T(0.5) , 15 );
  TTS_ULP_EQUAL(eve::betainc(T(0.2), T(0.3), T(2)), T(7.651219897728122e-01), 30);

  auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
  auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
  auto f1 = [](auto x){return eve::betainc(x,T{0.3},T{2});};

  TTS_ULP_EQUAL(eve::diff_1st(eve::betainc)(T{0.5},T{0.3},T{2}), df(f1, T(0.5)), ulp);
  TTS_ULP_EQUAL(eve::diff_1st(eve::betainc)(T{0.2},T{0.3},T{2}), df(f1, T(0.2)), ulp);
};
