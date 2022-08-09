//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/combinatorial.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::fibonacci", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using i_t   = eve::as_integer_t<T, unsigned>;
  using elt_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::fibonacci(i_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fibonacci(std::uint8_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fibonacci(i_t(), elt_t(), T()), T);
  TTS_EXPR_IS(eve::fibonacci(i_t(), T(), elt_t()), T);
  TTS_EXPR_IS(eve::fibonacci(i_t(), elt_t(), elt_t()), T);
  TTS_EXPR_IS(eve::fibonacci(std::uint8_t(), elt_t(), elt_t()), elt_t);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::fibonacci on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using i_t = eve::as_integer_t<T, unsigned>;
  TTS_EQUAL(eve::fibonacci(9u, T(1), T(1)), T(55));
  TTS_EQUAL(eve::fibonacci(i_t(9), T(1), T(1)), T(55));
};
