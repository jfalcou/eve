//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::lrising_factorial", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(eve::raw(eve::lrising_factorial)(int(), T()), T);
  TTS_EXPR_IS(eve::lrising_factorial(int(), T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::lrising_factorial)(int(), T()), T);
};

//==================================================================================================
//==  Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::lrising_factorial on wide",
             eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  auto ulp = sizeof(eve::element_type_t<T>) == 4 ? 70 : 20;
  TTS_ULP_EQUAL(eve::lrising_factorial(T(20), T(2.0)), T(6.040254711277414e+00), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(10, T(0.1)), T(2.256992585517679e-01), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(5, T(0.1)), T(1.517103381272788e-01), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(0, T(0.1)), eve::nan(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(2, T(0.1)), T(4.543773854448513e-02), ulp);
  TTS_ULP_EQUAL(eve::lrising_factorial(T(20.3), T(10.2)), T(3.272013434873217e+01), ulp);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(eve::nan(eve::as<T>()), T(2.5)),
                  eve::nan(eve::as<T>()),
                  0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(T(4.9), eve::nan(eve::as<T>())),
                  eve::nan(eve::as<T>()),
                  0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(eve::inf(eve::as<T>()), T(2.5)),
                  eve::nan(eve::as<T>()),
                  0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(T(4.9), eve::inf(eve::as<T>())),
                  eve::inf(eve::as<T>()),
                  0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(eve::minf(eve::as<T>()), T(2.5)),
                  eve::nan(eve::as<T>()),
                  0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(T(4.9), eve::minf(eve::as<T>())),
                  eve::inf(eve::as<T>()),
                  0); // verify
  }
  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(20), T(2.0)), T(6.040254711277414e+00), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(10, T(0.1)), T(2.256992585517679e-01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(5, T(0.1)), T(1.517103381272788e-01), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(0, T(0.1)), eve::minf(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(2, T(0.1)), T(4.543773854448513e-02), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(20.3), T(10.2)), T(3.272013434873217e+01), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(-20), T(-2.0)), T(-6.1355648910817386366), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(T(20), T(-20)), T(eve::lgamma(T(21))), ulp);
  TTS_ULP_EQUAL(eve::pedantic(eve::lrising_factorial)(T(-20), T(20)), eve::inf(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(-20), T(10.3)), eve::minf(eve::as<T>()), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(-20.2), T(-10.3)), T(-33.961897962564812303), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(-20.2), T(10.3)), T(28.713944249477066251), ulp);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(-20.2), T(30.4)), T(54.518836763604106466), ulp);
  elt_t r =
      sizeof(eve::element_type_t<T>) == 4 ? 1.7954323539015604183e-06 : 3.3442530265754862841e-15;
  TTS_ULP_EQUAL(
      eve::pedantic(eve::lrising_factorial)(T(5), 10 * eve::eps(eve::as<T>())), T(r), ulp);

  ulp = 110.0;
};


//==================================================================================================
// Tests for masked lrising_factorial
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::lrising_factorial)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           T const& a1,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::lrising_factorial[mask](a0, a1),
            eve::if_else(mask, eve::lrising_factorial(a0, a1), a0));
};
