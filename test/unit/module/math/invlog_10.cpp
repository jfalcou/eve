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
EVE_TEST_TYPES( "Check return types of invlog10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invlog_10(as<T>())  , T);
  TTS_EXPR_IS( eve::invlog_10(as<v_t>()), v_t);
};

//==================================================================================================
// invlog_10  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invlog_10 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::invlog_10(as<T>()),  T(0.43429448190325182765112891891660508229439700580367l));
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    TTS_EXPECT(downward(eve::invlog_10)(as<elt_t>()) < 0.43429448190325182765112891891660508229439700580367l);
    TTS_EXPECT(upward(eve::invlog_10)(as<elt_t>())   > 0.43429448190325182765112891891660508229439700580367l);
  }
  TTS_ULP_EQUAL(eve::invlog_10(as<T>()), T(0.43429448190325182765112891891660508229439700580367l), 0.0);
  TTS_EXPECT(eve::all(downward(eve::invlog_10)(as<T>()) <= eve::invlog_10(as<T>())));
  TTS_EXPECT(eve::all(eve::invlog_10(as<T>()) <= upward(eve::invlog_10)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invlog_10)(as<T>()), upward(eve::invlog_10)(as<T>()), 0.5);
};
