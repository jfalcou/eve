//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/special.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of stirling"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::stirling(T())  , T);
  TTS_EXPR_IS( eve::stirling(v_t()), v_t);
};

//==================================================================================================
// stirling  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of stirling on wide"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  using eve::stirling;
  using eve::as;

   if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(stirling(eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(stirling(eve::minf(eve::as<T>()) ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(stirling(eve::mone(eve::as<T>()) ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(stirling(eve::nan(eve::as<T>())  ) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::round(stirling(T(1))), T(1), 0.5);
  TTS_ULP_EQUAL(eve::round(stirling(T(2))), T(1), 0.5);
  TTS_ULP_EQUAL(eve::round(stirling(T(3))), T(2), 0.5);
};
