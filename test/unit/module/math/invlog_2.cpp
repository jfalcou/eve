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
EVE_TEST_TYPES( "Check return types of invlog_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invlog_2(as<T>())  , T);
  TTS_EXPR_IS( eve::invlog_2(as<v_t>()), v_t);
};

//==================================================================================================
// invlog_2  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invlog_2 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    using elt_t = eve::element_type_t<T>;
    TTS_EXPECT(downward(eve::invlog_2)(as<elt_t>()) < 1.442695040888963407359924681001892137426645954153l);
    TTS_EXPECT(upward(eve::invlog_2)(as<elt_t>())   > 1.442695040888963407359924681001892137426645954153l);
  }
  TTS_ULP_EQUAL(eve::invlog_2(as<T>()), T(1.442695040888963407359924681001892137426645954153l), 0.0);
  TTS_EXPECT(eve::all(downward(eve::invlog_2)(as<T>()) <= eve::invlog_2(as<T>())));
  TTS_EXPECT(eve::all(eve::invlog_2(as<T>()) <= upward(eve::invlog_2)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invlog_2)(as<T>()), upward(eve::invlog_2)(as<T>()), 0.5);
};
