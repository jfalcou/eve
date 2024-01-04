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
TTS_CASE_TPL("Check return types of invlog_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::invlog_2(as<T>()), T);
  TTS_EXPR_IS(eve::invlog_2(as<v_t>()), v_t);
};
//==================================================================================================
// invlog_2  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::invlog_2[eve::downward](as<elt_t>())
               < 1.442695040888963407359924681001892137426645954153l);
    TTS_EXPECT(eve::invlog_2[eve::upward](as<elt_t>())
               > 1.442695040888963407359924681001892137426645954153l);
  }
  TTS_IEEE_EQUAL(eve::invlog_2(as<T>()), T(1.442695040888963407359924681001892137426645954153l));
};

//==================================================================================================
// invlog_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_2 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::invlog_2[eve::downward](as<T>())), eve::invlog_2[eve::upward](as<T>()))));
};
