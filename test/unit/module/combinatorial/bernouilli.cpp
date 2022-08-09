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
TTS_CASE_TPL("Check return types of eve::bernouilli", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::bernouilli(T()), d_t);
  TTS_EXPR_IS(eve::bernouilli(v_t()), double);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::bernouilli on wide",
             eve::test::simd::unsigned_integers

)
<typename T>(tts::type<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::bernouilli(T(10)), d_t(5.0 / 66));
  TTS_EQUAL(eve::bernouilli(T(4)), d_t(-1.0 / 30));
  TTS_EQUAL(eve::bernouilli(T(0)), d_t(1));
  TTS_EQUAL(eve::bernouilli(T(1)), d_t(-0.5));
};
