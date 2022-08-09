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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::factorial", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  if constexpr( eve::integral_value<T> )
  {
    TTS_EXPR_IS(eve::factorial(T()), d_t);
    TTS_EXPR_IS(eve::factorial(v_t()), double);
  }
  else
  {
    TTS_EXPR_IS(eve::factorial(T()), T);
    TTS_EXPR_IS(eve::factorial(v_t()), v_t);
  }
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::factorial on wide", eve::test::simd::all_types

)
<typename T>(tts::type<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL(eve::factorial(T(10)), d_t(3628800));
    TTS_EQUAL(eve::factorial(T(5)), d_t(120));
    TTS_EQUAL(eve::factorial(T(0)), d_t(1));
    TTS_EQUAL(eve::factorial(T(1)), d_t(1));
  }
  else
  {
    TTS_EQUAL(eve::factorial(T(10)), T(3628800));
    TTS_EQUAL(eve::factorial(T(5)), T(120));
    TTS_EQUAL(eve::factorial(T(0)), T(1));
    TTS_EQUAL(eve::factorial(T(1)), T(1));
  }
};
