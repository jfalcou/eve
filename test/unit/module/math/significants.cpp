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
//  using muint =  unsigned int;
  TTS_EXPR_IS(eve::significants(T(), uint()), T);
  TTS_EXPR_IS(eve::significants(v_t(), uint()), v_t);
};

TTS_CASE_TPL("Check significants", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_IEEE_EQUAL(eve::significants(T(1.234567), 0u), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 1u), T(1.), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 2u), T(1.2), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 3u), T(1.23), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(1.234567), 4u), T(1.235), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 1u), T(0.01), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 2u), T(0.012), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 3u), T(0.0123), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(0.01234567), 4u), T(0.01235), 0.5);

  TTS_IEEE_EQUAL(eve::significants(T(-1.234567), 0u), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 1u), T(-1.), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 2u), T(-1.2), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 3u), T(-1.23), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-1.234567), 4u), T(-1.235), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 1u), T(-0.01), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 2u), T(-0.012), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 3u), T(-0.0123), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(-0.01234567), 4u), T(-0.01235), 0.5);

  TTS_IEEE_EQUAL(eve::significants(T(0), 0u), eve::nan(eve::as<T>()));
  TTS_EQUAL(eve::significants(T(0), 1u), T(0));
  TTS_EQUAL(eve::significants(T(0), 2u), T(0));
  TTS_EQUAL(eve::significants(T(0), 3u), T(0));
  TTS_EQUAL(eve::significants(T(0), 4u), T(0));

  TTS_IEEE_EQUAL(eve::significants(T(987654321), 0u), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 1u), T(1000000000.0));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 2u), T(990000000.0));
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 3u), T(988000000.0));
  TTS_ULP_EQUAL(eve::significants(T(987654321), 4u), T(987700000.0), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(987654321), 5u), T(987650000.0), 0.5);
  TTS_ULP_EQUAL(eve::significants(T(987654321), 6u), T(987654000.0), 0.5);
};
