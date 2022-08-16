//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/value.hpp>
#include <eve/module/math.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of significants", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::significants(T(), int()), T);
  TTS_EXPR_IS(eve::significants(v_t(), int()), v_t);
};

TTS_CASE_TPL("Check significants", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_IEEE_EQUAL(eve::significants(T(1.234567), 0), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 1), T(1.), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 2), T(1.2), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 3), T(1.23), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 4), T(1.235), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 1), T(0.01), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 2), T(0.012), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 3), T(0.0123), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 4), T(0.01235), 0.5);

  TTS_IEEE_EQUAL(eve::significants(T(-1.234567), 0), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 1), T(-1.), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 2), T(-1.2), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 3), T(-1.23), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 4), T(-1.235), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 1), T(-0.01), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 2), T(-0.012), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 3), T(-0.0123), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 4), T(-0.01235), 0.5);

  TTS_IEEE_EQUAL(eve::significants(T(0), 0), eve::nan(eve::as<T>()));
  TTS_EQUAL(eve::significants(T(0), 1), T(0));
  TTS_EQUAL(eve::significants(T(0), 2), T(0));
  TTS_EQUAL(eve::significants(T(0), 3), T(0));
  TTS_EQUAL(eve::significants(T(0), 4), T(0));

  TTS_IEEE_EQUAL(eve::significants(T(987654321), 0), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 1), T(1000000000.0));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 2), T(990000000.0));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 3), T(988000000.0));
  TTS_ULP_EQUAL(eve::significants(T(987654321), 4), T(987700000.0), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(987654321), 5), T(987650000.0), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(987654321), 6), T(987654000.0), 0.5);
};
