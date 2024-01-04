//revised
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
TTS_CASE_TPL("Check return types of invlog10", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::invlog_10(as<T>()), T);
  TTS_EXPR_IS(eve::invlog_10(as<v_t>()), v_t);
};
//==================================================================================================
// invlog_10  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_10 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EQUAL(eve::invlog_10(as<T>()), T(0.43429448190325182765112891891660508229439700580367l));
};

//==================================================================================================
// invlog_10  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_10 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::invlog_10[eve::downward](as<elt_t>())
               < 0.43429448190325182765112891891660508229439700580367l);
    TTS_EXPECT(eve::invlog_10[eve::upward](as<elt_t>())
               > 0.43429448190325182765112891891660508229439700580367l);
  }
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::invlog_10[eve::downward](as<T>())), eve::invlog_10[eve::upward](as<T>()))));
};
