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
EVE_TEST_TYPES( "Check return types of maxlog"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::maxlog(as<T>())  , T);
  TTS_EXPR_IS( eve::maxlog(as<v_t>()), v_t);
};

//==================================================================================================
// maxlog  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of maxlog on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp(eve::maxlog(as<T>())), eve::inf(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog(as<T>()))))));
};
