/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of modf", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using wtyp = kumi::tuple<T, T>;
  using typ  = kumi::tuple<v_t, v_t>;
  TTS_EXPR_IS(eve::modf(T()), wtyp);
  TTS_EXPR_IS(eve::modf(v_t()), typ);
};

//==================================================================================================
//== modf  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of modf on all types full range", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  {
    auto [p0, p1] = eve::modf(T(1.5));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  if constexpr( eve::signed_value<T> )
  {
    auto [p0, p1] = eve::modf(T(-1.6));
    TTS_ULP_EQUAL(p0, T(-0.6), 0.5);
    TTS_EQUAL(p1, T(-1));
  }
  {
    auto [p0, p1] = eve::pedantic(eve::modf)(T(1.5));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  if constexpr( eve::signed_value<T> )
  {
    auto [p0, p1] = eve::pedantic(eve::modf)(T(-1.6));
    TTS_ULP_EQUAL(p0, T(-0.6), 0.5);
    TTS_EQUAL(p1, T(-1));
  }
};
