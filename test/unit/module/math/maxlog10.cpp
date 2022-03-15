//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of maxlog10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::maxlog10(as<T>())  , T);
  TTS_EXPR_IS( eve::maxlog10(as<v_t>()), v_t);
};

//==================================================================================================
// maxlog10  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of maxlog10 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp10(eve::maxlog10(as<T>())), eve::inf(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog10(as<T>()))))));
};
